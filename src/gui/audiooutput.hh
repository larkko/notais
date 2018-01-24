#pragma once

#include <memory>
#include <tuple>

#include <RtAudio.h>

#include "../lib/audio/audiodata.hh"

class Audio_output
{
  public:
    Audio_output();
    void start();
    void stop();
    bool is_active();
    Audio_data & active_buffer();
    Audio_data & back_buffer();
  private:
    static constexpr unsigned int m_sample_rate = 44100;
    static constexpr unsigned int m_buffer_size = 256;
    static constexpr unsigned int m_channel_count = 1;
    RtAudio m_out;
    bool m_active;
    std::tuple<Audio_data, Audio_data> m_buffers;
    /*Denotes which buffer is active*/
    bool m_buffer_flag;
};