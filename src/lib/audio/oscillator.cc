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
    double wave_offset,
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

Audio_data::Sample Oscillator::get_sample
(
    float frequency,
    Audio_source::Offset offset
) const
{
    double sine_multiplier = 2.0 * M_PI;
    double wave_offset = offset * frequency * sine_multiplier;
    Audio_data::Sample sample = 0.0f;
    switch(m_type)
    {
        case Oscillator::Type::Sine:
            sample = sin(wave_offset);
            break;
        default:
            sample = square_saw_at(wave_offset, m_type);
            break;
    }
    
    return sample;
}

void Oscillator::set_type(Oscillator::Type type)
{
    m_type = type;
}



