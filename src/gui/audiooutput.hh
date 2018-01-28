#pragma once

#include <memory>
#include <tuple>
#include <functional>

#include <RtAudio.h>

#include "../lib/audio/audiodata.hh"

class Audio_output
{
  public:
    Audio_output(std::function<void (Audio_data &)> callback);
    void start();
    void stop();
    bool is_active() const;
    void set_volume(float volume);
    float volume() const;
    Audio_data & buffer();
    std::function<void (Audio_data &)> const buffer_fill_callback;
  private:
    static constexpr unsigned int m_sample_rate = 44100;
    static constexpr unsigned int m_buffer_size = 256;
    static constexpr unsigned int m_channel_count = 1;
    RtAudio m_out;
    bool m_active;
    Audio_data m_buffer;
    float m_volume;
};