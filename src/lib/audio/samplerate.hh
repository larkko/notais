#pragma once

#include <cstddef>

class Sample_rate
{
  public:
    Sample_rate(size_t rate);
    size_t seconds_to_samples(double seconds);
    double samples_to_seconds(size_t samples);
    size_t rate() const;
  private:
    size_t m_rate;
};
