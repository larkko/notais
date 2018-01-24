/*Gives us the M_PI constant*/
#define _USE_MATH_DEFINES
#include <math.h>

#include "oscillator.hh"

Oscillator::Oscillator(Oscillator::Type type)
    : m_type(type)
{

}

void Oscillator::get_samples
(
    Audio_data & destination,
    float frequency,
    size_t sample_count,
    size_t offset_in_source,
    size_t offset_in_destination
) const
{
    size_t sample_rate = destination.sample_rate();
    float multiplier = frequency / static_cast<float>(sample_rate);
    float sine_multiplier = multiplier * 2.0f * M_PI;
    for(size_t i = offset_in_source; i < (offset_in_source + sample_count); ++i)
    {
        Audio_data::Sample sample = 0.0f;
        switch(m_type)
        {
            case Oscillator::Type::Sine:
                sample = sin(sine_multiplier * static_cast<float>(i));
                break;
            default:
                break;
        }
        for(size_t c = 0; c < destination.channel_count(); ++c)
        {
            destination.set_sample(i + offset_in_destination, c, sample);
        }
    }
}