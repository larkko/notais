/*Gives us the M_PI constant*/
#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>
#include <cstdlib>
#include <algorithm>

#include "oscillator.hh"

Oscillator::Oscillator(Oscillator::Type type)
    : m_type(type)
{

}

Audio_data::Sample random_sample()
{
    Audio_data::Sample value_offset = Audio_data::max_amplitude / 2.0;
    Audio_data::Sample value_multiplier = Audio_data::max_amplitude * 2.0;
    Audio_data::Sample result = ((float(std::rand())
                                  / float(RAND_MAX))
                                - value_offset) * value_multiplier;
    return result;
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
            sample = Audio_data::max_amplitude * sinf(wave_offset);
            break;
        case Oscillator::Type::White_noise:
            sample = random_sample();
            break;
        default:
        {
            float resulting_amplitude = 0.0f;
            Audio_data::Sample layered_sample = 0.0f;
            /*Exact number doesn't matter, just stack enough to approximate
              a decent saw/square wave*/
            int const harmonic_count = 15;
            /*For square waves, skip every even harmonic*/
            int const harmonic_step = (m_type == Oscillator::Type::Saw)
                                    ? 1
                                    : 2; 
            for(int harmonic = 1; harmonic < harmonic_count; harmonic += harmonic_step)
            {
                layered_sample += sinf(wave_offset * harmonic);
                resulting_amplitude += 1.0f / harmonic;
            }
            sample = Audio_data::max_amplitude * layered_sample / resulting_amplitude;
        } break;
    }
    
    return sample;
}

std::string Oscillator::description() const
{
    return std::string("Oscillator (")
           + ((m_type == Type::Sine) ? "Sine"
             : (m_type == Type::Saw) ? "Saw"
             : (m_type == Type::Square) ? "Square"
             : (m_type == Type::White_noise) ? "White noise" : "")
           + ")";
}

void Oscillator::set_type(Oscillator::Type type)
{
    m_type = type;
}



