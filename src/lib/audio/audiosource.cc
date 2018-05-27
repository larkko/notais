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

double Audio_source::Offset::time_since_release() const
{
    return released() ? (offset() - release_offset()) : 0.0;
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
    size_t release_offset,
    size_t offset_in_destination
) const
{
    Sample_rate sample_rate = destination.sample_rate();
    for(size_t i = 0; i < sample_count; ++i)
    {
        double seconds_passed = sample_rate.samples_to_seconds(i + offset_in_source);
        bool released = release_offset != 0;
        Offset offset = released
                      ? Offset(seconds_passed,
                               destination.sample_rate()
                                          .samples_to_seconds(release_offset))
                      : Offset(seconds_passed);
        Audio_data::Sample sample = volume
                                  * get_sample(frequency, offset);
        for(size_t c = 0; c < destination.channel_count(); ++c)
        {
            destination.add_to_sample(i + offset_in_destination, c, sample);
        }
    }
}

Audio_data Audio_source::data_for
(
    float frequency,
    size_t frame_count,
    Sample_rate sample_rate,
    size_t channel_count
)
{
    Audio_data result(sample_rate, channel_count);
    result.reserve(frame_count);
    for(size_t f = 0; f < frame_count; ++f)
    {
        for(size_t c = 0; c < channel_count; ++c)
        {
            result.set_sample
            (
                f,
                c,
                get_sample(frequency, Offset(sample_rate.samples_to_seconds(f)))
            );
        }
    }
    return result;
}

double Audio_source::linger_time() const
{
    return 0.0;
}
