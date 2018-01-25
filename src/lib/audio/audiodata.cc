#include "audiodata.hh"

Audio_data::Audio_data(size_t sample_rate, size_t channel_count)
    : m_sample_rate(sample_rate), m_channel_count(channel_count)
{

}

void Audio_data::reserve(size_t sample_count)
{
    size_t reserve_size = sample_count * m_channel_count;
    m_samples.reserve(reserve_size);
    auto size = m_samples.size();
    for(auto i = size; i < reserve_size; ++i)
    {
        m_samples.push_back(0.0f);
    }
}


Audio_data::Sample Audio_data::sample_at(size_t index, size_t channel)
{
    return m_samples[sample_index(index, channel)];
}

void Audio_data::set_sample(size_t index, size_t channel, Sample value)
{
    m_samples[sample_index(index, channel)] = value;
}

void Audio_data::add_to_sample(size_t index, size_t channel, Sample value)
{
    m_samples[sample_index(index, channel)] += value;
}

void Audio_data::reset()
{
    for(auto & s : m_samples)
    {
        s = 0.0f;
    }
}

void Audio_data::clamp_samples()
{
    for(auto & s : m_samples)
    {
        s = (s > 1.0f) ? 1.0f
          : (s < -1.0f) ? -1.0f
          : s;
    }
}

size_t Audio_data::sample_rate()
{
    return m_sample_rate;
}

size_t Audio_data::channel_count()
{
    return m_channel_count;
}

size_t Audio_data::sample_count()
{
    return m_samples.size();
}

size_t Audio_data::frame_count()
{
    return sample_count() / channel_count();
}

size_t Audio_data::sample_index(size_t nth, size_t channel)
{
    return channel + (nth * m_channel_count);
}