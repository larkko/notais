#pragma once

#include <vector>
#include <cstddef>

class Audio_data
{
  public:
    typedef float Sample;
    Audio_data(size_t sample_rate, size_t channel_count);
    /*Reserves sample_count samples for each channel*/
    void reserve(size_t sample_count);
    Sample sample_at(size_t index, size_t channel) const;
    void set_sample(size_t index, size_t channel, Sample value);
    void add_to_sample(size_t index, size_t channel, Sample value);
    /*Sets the data in an Audio_data instance to silence.*/
    void reset();
    /*Ensures no samples are out of bounds*/
    void clamp_samples();
    void multiply_all_samples(float multiplier);
    size_t sample_rate() const;
    size_t channel_count() const;
    /*Number of individual samples*/
    size_t sample_count() const;
    /*Number of frames (i.e. samples / channels)*/
    size_t frame_count() const;
  private:
    std::vector<Sample> m_samples;
    size_t m_sample_rate;
    size_t m_channel_count;
    size_t sample_index(size_t nth, size_t channel) const;
};

