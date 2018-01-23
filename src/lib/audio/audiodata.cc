#include "audiodata.hh"

Audio_data::Audio_data(size_t sample_rate, size_t channel_count)
    : m_sample_rate(sample_rate), m_channel_count(channel_count)
{

}

void Audio_data::reserve(size_t sample_count)
{
    m_samples.reserve(sample_count * m_channel_count);
}
