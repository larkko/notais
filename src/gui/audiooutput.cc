#include "audiooutput.hh"

#include <cmath>

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
      m_out(RtAudio()),
      m_active(false),
      m_buffer(Audio_data(m_sample_rate, m_channel_count)),
      m_volume(0.1f),
      /*2 is right for my system, change to default once selection widget
        exists.*/
      m_device_index(2)
{
    set_buffer_frame_count(m_buffer_frame_count);
}

void Audio_output::start()
{
    if(m_out.getDeviceCount() < 1)
    {
        std::cout << "No audio devices found." << std::endl;
    }

    RtAudio::StreamParameters parameters;
    parameters.deviceId = m_device_index;
    parameters.nChannels = m_channel_count;

    unsigned int buffer_size = m_buffer_frame_count;

    try
    {
        m_out.openStream(&parameters, NULL, RTAUDIO_FLOAT32,
                         m_sample_rate, &buffer_size,
            [](void * output_buffer,
               void * input_buffer,
               unsigned int buffer_frame_count,
               double stream_time,
               RtAudioStreamStatus status,
               void * user_data)
            {
                /*Disregard unused parameters*/
                (void)input_buffer;
                (void)stream_time;

                if(status)
                {
                    std::cout << "Error in stream callback" << std::endl;
                }

                Audio_output * out = static_cast<Audio_output *>(user_data);

                float volume = out->volume();

                Audio_data & data = out->buffer();

                /*Set to appropriate volume and clamp to acceptable bounds*/
                data.multiply_all_samples(volume);
                data.clamp_samples();

                /*Put old buffer contents into output buffer*/
                float * buffer = (float *)output_buffer;
                for(unsigned int i = 0; i < buffer_frame_count; ++i)
                {
                    for(unsigned int c = 0; c < out->channel_count(); ++c)
                    {
                        float val = volume * (data.sample_at(i, c));
                        *buffer++ = val;
                    }
                }

                data.reset();

                /*Put new content in buffer*/
                out->buffer_fill_callback(out->buffer());

                return 0;
            },
            /*User data*/
            (void *)this);
        m_out.startStream();
        m_active = true;
    }
    catch(RtAudioError & error)
    {
        error.printMessage();
    }
}

void Audio_output::stop()
{
    try
    {
        m_out.stopStream();
    }
    catch(RtAudioError & error)
    {
        error.printMessage();
    }

    if(m_out.isStreamOpen())
    {
        m_out.closeStream();
    }

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
    stop();
    m_sample_rate = sample_rate;
    reconfigure_buffer();
}

size_t Audio_output::buffer_frame_count() const
{
    return m_buffer_frame_count;
}

void Audio_output::set_buffer_frame_count(size_t buffer_frame_count)
{    
    stop();
    m_buffer_frame_count = buffer_frame_count;
    reconfigure_buffer();
}

size_t Audio_output::channel_count() const
{
    return m_channel_count;
}

void Audio_output::set_channel_count(size_t channel_count)
{    
    stop();
    m_channel_count = channel_count;
    reconfigure_buffer();
}

size_t Audio_output::device_count()
{
    return m_out.getDeviceCount();
}

void Audio_output::set_device(size_t device_index)
{
    if(device_index < device_count())
    {
        stop();
        m_device_index = device_index;
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



