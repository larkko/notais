#pragma once

#include <cstddef>

class Sample_rate
{
  public:
    Sample_rate(size_t rate);
    size_t seconds_to_samples(double seconds);
    double samples_to_seconds(size_t samples);
  private:
    size_t m_rate;
};
