#include "audiodata.hh"

#include <sndfile.hh>

Audio_data::Audio_data(Sample_rate sample_rate, size_t channel_count)
    : m_sample_rate(sample_rate), m_channel_count(channel_count)
{

}

void Audio_data::reserve(size_t frame_count)
{
    size_t reserve_size = frame_count * m_channel_count;
    m_samples.reserve(reserve_size);
    auto size = m_samples.size();
    for(auto i = size; i < reserve_size; ++i)
    {
        m_samples.push_back(0.0f);
    }
}


Audio_data::Sample Audio_data::sample_at(size_t index, size_t channel) const
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
        s = (s > max_amplitude) ? max_amplitude
          : (s < -max_amplitude) ? -max_amplitude
          : s;
    }
}

void Audio_data::multiply_all_samples(float multiplier)
{
    for(auto & s : m_samples)
    {
        s = s * multiplier;
    }
}

Sample_rate Audio_data::sample_rate() const
{
    return m_sample_rate;
}

size_t Audio_data::channel_count() const
{
    return m_channel_count;
}

size_t Audio_data::sample_count() const
{
    return m_samples.size();
}

size_t Audio_data::frame_count() const
{
    return sample_count() / channel_count();
}

void Audio_data::save(std::string filename) const
{
    SndfileHandle file
    (
        filename,
        SFM_WRITE,
        SF_FORMAT_WAV | SF_FORMAT_PCM_32 | SF_FORMAT_FLOAT,
        int(channel_count()),
        int(sample_rate().rate())
    );
    file.write(m_samples.data(), m_samples.size());
}

size_t Audio_data::sample_index(size_t nth, size_t channel) const
{
    return channel + (nth * m_channel_count);
}
