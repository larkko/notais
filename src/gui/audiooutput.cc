#include "audiooutput.hh"

#include <cmath>

Audio_output::Audio_output()
    : m_out(RtAudio())
{
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
    parameters.nChannels = 1;
    unsigned int sample_rate = 44100;
    unsigned int buffer_size = 256;

    try
    {
        m_out.openStream(&parameters, NULL, RTAUDIO_FLOAT32,
                         sample_rate, &buffer_size,
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
                float * buffer = (float *)output_buffer;
                for(unsigned int i = 0; i < buffer_frame_count; ++i)
                {
                    float freq = 440.0f;
                    float val = 0.1f * sin(2.0f*3.1415f*freq*(stream_time + (float)i/44100.0f));
                    
                    *buffer++ = val;
                }
                return 0;
            },
            /*User data*/
            (void *)this);
        m_out.startStream();
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
}















