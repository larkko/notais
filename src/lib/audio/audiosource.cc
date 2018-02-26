#include "audiosource.hh"

#include <iostream>

Audio_source::Offset::Offset
(
    double offset,
    double release_offset
)
    : m_offset(offset),
      m_release_offset(release_offset)
{

}

double Audio_source::Offset::offset() const
{
    return m_offset;
}

double Audio_source::Offset::release_offset() const
{
    return m_release_offset;
}

bool Audio_source::Offset::released() const
{
    return !((m_release_offset < 0.0) || (m_release_offset > m_offset));
}

Audio_source::Offset::operator double() const
{
    return offset();
}

void Audio_source::get_samples
(
    Audio_data & destination,
    float frequency,
    float volume,
    size_t sample_count,
    size_t offset_in_source,
    size_t offset_in_destination
) const
{
    Sample_rate sample_rate = destination.sample_rate();
    for(size_t i = 0; i < sample_count; ++i)
    {
        double seconds_passed = sample_rate.samples_to_seconds(i + offset_in_source);
        Audio_data::Sample sample = volume
                                  * get_sample(frequency, seconds_passed);
        for(size_t c = 0; c < destination.channel_count(); ++c)
        {
            destination.add_to_sample(i + offset_in_destination, c, sample);
        }
    }
}

float Audio_source::linger_time() const
{
    return 0.0;
}
