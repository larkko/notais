#include "samplerate.hh"

Sample_rate::Sample_rate(size_t rate)
    : m_rate(rate)
{
}

size_t Sample_rate::seconds_to_samples(double seconds)
{
    return size_t(seconds * m_rate);
}

double Sample_rate::samples_to_seconds(size_t samples)
{
    return double(samples)/double(m_rate);
}

size_t Sample_rate::rate() const
{
    return m_rate;
}
