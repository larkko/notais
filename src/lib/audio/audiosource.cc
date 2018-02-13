#include "audiosource.hh"

#include <iostream>

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
    for(size_t i = 0; i < sample_count; ++i)
    {
        double sample_offset = double(i + offset_in_source)
                             / double(destination.sample_rate());
        double seconds_passed = sample_offset;
        Audio_data::Sample sample = volume
                                  * get_sample(frequency, seconds_passed);
        for(size_t c = 0; c < destination.channel_count(); ++c)
        {
            destination.add_to_sample(i + offset_in_destination, c, sample);
        }
    }
}