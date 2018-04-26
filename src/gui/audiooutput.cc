#include "audiooutput.hh"

#include <cmath>
#include <memory>
#include <cstddef>
#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
#include <string>

#include "alsa/asoundlib.h"

class ALSA_audio_output_implementation : public Audio_output_implementation
{
  public:
    ALSA_audio_output_implementation()
        : m_thread(std::make_shared<std::thread>(std::thread())),
          m_out(nullptr),
          m_on(std::make_shared<std::atomic<bool>>(false))
    {
    }
    ~ALSA_audio_output_implementation();
    virtual bool start
    (
        Audio_data & buffer,
        size_t sample_rate,
        size_t frame_count,
        size_t channel_count,
        std::function<void (Audio_data &)> callback
    ) override;
    virtual void stop() override;
    virtual bool on() const override { return m_on->load(); }
  private:
    std::vector<std::string> device_names();
    std::shared_ptr<std::thread> m_thread;
    snd_pcm_t * m_out;
    std::shared_ptr<std::atomic<bool>> m_on;
};

ALSA_audio_output_implementation::~ALSA_audio_output_implementation()
{
    stop();
    if(m_thread->joinable())
    {
        m_thread->join();
    }
}

bool ALSA_audio_output_implementation::start
(
    Audio_data & buffer,
    size_t sample_rate,
    size_t frame_count,
    size_t channel_count,
    std::function<void (Audio_data &)> callback
)
{
    auto open_result = snd_pcm_open
    (
        &m_out,
        "default",
        SND_PCM_STREAM_PLAYBACK,
        0
    );
    
    if(open_result < 0)
    {
        std::cerr << "Failed to open ALSA stream: "
                  << snd_strerror(open_result) << std::endl;
        return false;
    }
    
    /*ALSA wants this in microseconds.
      Let's choose just about two frames as the limit.*/
    auto latency_limit = 1000000 / ((sample_rate / frame_count) / 2 + 1);
    
    auto setup_result = snd_pcm_set_params
    (
        m_out,
        SND_PCM_FORMAT_FLOAT,
        SND_PCM_ACCESS_RW_INTERLEAVED,
        channel_count,
        sample_rate,
        1,
        latency_limit
    );
    
    if(setup_result < 0)
    {
        std::cerr << "Failed to set ALSA audio params: "
                  << snd_strerror(setup_result) << std::endl;
        return false;
    }
    
    std::shared_ptr<float> raw_buffer
    (
        new float[frame_count * channel_count],
        std::default_delete<float[]>()
    );
 
    m_thread = std::make_shared<std::thread>
    (
        [=, &buffer]()
        {
            m_on->store(true);
            bool quit = false;
            while(!quit && m_on->load())
            {
                callback(buffer);
                
                for(size_t i = 0; i < frame_count; ++i)
                {
                    for(size_t c = 0; c < channel_count; ++c)
                    {
                        auto & sample = raw_buffer.get()[i*channel_count + c];
                        auto source_sample = buffer.sample_at(i, c);
                        sample = source_sample;
                    }
                }
                
                auto frames_written = snd_pcm_writei
                (
                    m_out,
                    raw_buffer.get(),
                    frame_count
                );
                if(frames_written < 0)
                {
                    frames_written = snd_pcm_recover(m_out, frames_written, 0);
                }
                if(frames_written < 0)
                {
                    std::cerr << "Failed to write ALSA data: "
                              << snd_strerror(frames_written) << std::endl;
                    quit = true;
                }
                else if(frames_written > 0 && frames_written < int(frame_count))
                {
                    std::cerr << "ALSA audio underflow" << std::endl;
                }
            }
            snd_pcm_close(m_out);
            m_on->store(false);
        }
    );
    
    return true;
}

void ALSA_audio_output_implementation::stop()
{
    m_on->store(false);
}

Audio_output::Audio_output
(
    size_t sample_rate,
    size_t buffer_frame_count,
    size_t channel_count,
    std::function<void (Audio_data &)> callback
)
    : buffer_fill_callback(callback),
      m_sample_rate(sample_rate),
      m_buffer_frame_count(buffer_frame_count),
      m_channel_count(channel_count),
      m_active(false),
      m_buffer(Audio_data(m_sample_rate, m_channel_count)),
      m_volume(0.1f),
      m_out
      (
          std::make_unique<ALSA_audio_output_implementation>
          (
            ALSA_audio_output_implementation()
          )
      )
{
    set_buffer_frame_count(m_buffer_frame_count);
}

void Audio_output::start()
{
    if(m_out)
    {
        bool success = m_out->start
        (
            m_buffer,
            m_sample_rate,
            m_buffer_frame_count,
            m_channel_count,
            [=](Audio_data & destination)
            {
                destination.reset();
                buffer_fill_callback(destination);
                destination.multiply_all_samples(m_volume);
                destination.clamp_samples();
            }
        );
        if(success) m_active = true;
    }
}

void Audio_output::stop()
{
    m_out->stop();
    m_active = false;
}

bool Audio_output::is_active() const
{
    return m_active;
}

void Audio_output::set_volume(float volume)
{
    if(volume >= 0.0f && volume <= 1.0f)
    {
        m_volume = volume;
    }
}

float Audio_output::volume() const
{
    return m_volume;
}

size_t Audio_output::sample_rate() const
{
    return m_sample_rate;
}

void Audio_output::set_sample_rate(size_t sample_rate)
{
    bool was_on = is_active();
    stop();
    m_sample_rate = sample_rate;
    reconfigure_buffer();
    if(was_on)
    {
        start();
    }
}

size_t Audio_output::buffer_frame_count() const
{
    return m_buffer_frame_count;
}

void Audio_output::set_buffer_frame_count(size_t buffer_frame_count)
{
    bool was_on = is_active();
    stop();
    m_buffer_frame_count = buffer_frame_count;
    reconfigure_buffer();
    if(was_on)
    {
        start();
    }
}

size_t Audio_output::channel_count() const
{
    return m_channel_count;
}

void Audio_output::set_channel_count(size_t channel_count)
{
    bool was_on = is_active();
    stop();
    m_channel_count = channel_count;
    reconfigure_buffer();
    if(was_on)
    {
        start();
    }
}

Audio_data & Audio_output::buffer()
{
    return m_buffer;
}

void Audio_output::reconfigure_buffer()
{
    m_buffer = Audio_data(m_sample_rate, m_channel_count);
    m_buffer.reserve(m_buffer_frame_count);
}



