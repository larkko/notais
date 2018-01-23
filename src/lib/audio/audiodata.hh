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
  private:
    std::vector<Sample> m_samples;
    size_t m_sample_rate;
    size_t m_channel_count;
};

