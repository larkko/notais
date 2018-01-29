#pragma once

#include <memory>
#include <tuple>
#include <functional>
#include <cstddef>

#include <RtAudio.h>

#include "../lib/audio/audiodata.hh"

class Audio_output
{
  public:
    Audio_output
    (
        size_t sample_rate,
        size_t buffer_frame_count,
        size_t channel_count,
        std::function<void (Audio_data &)> callback
    );
    void start();
    void stop();
    bool is_active() const;
    void set_volume(float volume);
    float volume() const;
    size_t sample_rate() const;
    void set_sample_rate(size_t sample_rate);
    size_t buffer_frame_count() const;
    void set_buffer_frame_count(size_t buffer_frame_count);
    size_t channel_count() const;
    void set_channel_count(size_t channel_count);
    size_t device_count();
    size_t device_index() const;
    void set_device(size_t device_index);
    std::string device_description(size_t device_index);
    Audio_data & buffer();
    std::function<void (Audio_data &)> const buffer_fill_callback;
  private:
    void reconfigure_buffer();
    size_t m_sample_rate;
    size_t m_buffer_frame_count;
    size_t m_channel_count;
    RtAudio m_out;
    bool m_active;
    Audio_data m_buffer;
    float m_volume;
    size_t m_device_index;
};