#include "audiooutput.hh"

#include <cmath>

Audio_output::Audio_output(std::function<void (Audio_data &)> callback)
    : buffer_fill_callback(callback),
      m_out(RtAudio()),
      m_active(false),
      m_buffer(Audio_data(m_sample_rate, m_channel_count))
{
    m_buffer.reserve(m_buffer_size);
}

void Audio_output::start()
{
    if(m_out.getDeviceCount() < 1)
    {
        std::cout << "No audio devices found." << std::endl;
    }

    RtAudio::StreamParameters parameters;
    /*This device (which is not the default output device) is the
      correct one on my system. Switch this to m_out.getDefaultOutputDevice()
      once audio output device selection is implemented*/
    parameters.deviceId = 2;
    parameters.nChannels = m_channel_count;

    unsigned int buffer_size = m_buffer_size;

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
                if(status)
                {
                    std::cout << "Error in stream callback" << std::endl;
                }

                Audio_output * out = static_cast<Audio_output *>(user_data);

                /*Put old buffer contents into output buffer*/
                float * buffer = (float *)output_buffer;
                for(unsigned int i = 0; i < buffer_frame_count; ++i)
                {
                    float val = out->buffer().sample_at(i, 0);
                    *buffer++ = val;
                }

                out->buffer().reset();

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

bool Audio_output::is_active()
{
    return m_active;
}

Audio_data & Audio_output::buffer()
{
    return m_buffer;
}




