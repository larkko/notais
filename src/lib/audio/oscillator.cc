/*Gives us the M_PI constant*/
#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>

#include "oscillator.hh"

Oscillator::Oscillator(Oscillator::Type type)
    : m_type(type)
{

}

Audio_data::Sample square_saw_at
(
    float wave_offset,
    Oscillator::Type type
)
{
    Audio_data::Sample sample = 0.0f;
    float resulting_amplitude = 0.0f;
    /*Exact number doesn't matter, just stack enough to approximate
      a decent saw/square wave*/
    int const harmonic_count = 15;
    /*For square waves, skip every even harmonic*/
    int const harmonic_step = (type == Oscillator::Type::Saw)
                            ? 1
                            : 2; 
    for(int harmonic = 1; harmonic < harmonic_count; harmonic += harmonic_step)
    {
        sample += sin(wave_offset * harmonic);
        resulting_amplitude += 1.0f / harmonic;
    }
    return sample / resulting_amplitude;
}

void Oscillator::get_samples
(
    Audio_data & destination,
    float frequency,
    float volume,
    size_t sample_count,
    size_t offset_in_source,
    size_t offset_in_destination
) const
{
    size_t sample_rate = destination.sample_rate();
    float multiplier = frequency / static_cast<float>(sample_rate);
    float sine_multiplier = multiplier * 2.0f * M_PI;
    for(size_t i = 0; i < sample_count; ++i)
    {
        size_t s = i + offset_in_source;
        auto wave_offset = sine_multiplier * s;
        Audio_data::Sample sample = 0.0f;
        switch(m_type)
        {
            case Oscillator::Type::Sine:
                sample = volume * sin(wave_offset);
                break;
            case Oscillator::Type::Saw:
                sample = volume * square_saw_at(wave_offset,
                                                Oscillator::Type::Saw);
                break;
            case Oscillator::Type::Square:
                sample = volume * square_saw_at(wave_offset,
                                                Oscillator::Type::Square);
                break;
            default: 
                break;
        }
        for(size_t c = 0; c < destination.channel_count(); ++c)
        {
            destination.add_to_sample(i + offset_in_destination, c, sample);
        }
    }
}