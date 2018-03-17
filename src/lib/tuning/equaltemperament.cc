#include "equaltemperament.hh"
#include <cmath>

Equal_temperament::Equal_temperament
(
    int steps_per_interval,
    float interval_size,
    float base_frequency
)
    : m_steps_per_interval(steps_per_interval),
      m_interval_size(interval_size),
      m_base_frequency(base_frequency)
{

}

float Equal_temperament::frequency_at(float steps) const
{
    return m_base_frequency * pow(step_multiplier(), steps);
}

int Equal_temperament::steps_in_pattern() const
{
    return steps_per_interval();
};

int Equal_temperament::steps_per_interval() const
{
    return m_steps_per_interval;
}

void Equal_temperament::set_steps_per_interval(int value)
{
    m_steps_per_interval = value;
}

float Equal_temperament::interval_size() const
{
    return m_interval_size;
}

void Equal_temperament::set_interval_size(float value)
{
    m_interval_size = value;
}

float Equal_temperament::base_frequency() const
{
    return m_base_frequency;
}

void Equal_temperament::set_base_frequency(float value)
{
    m_base_frequency = value;
}

float Equal_temperament::step_multiplier() const
{
    return pow(m_interval_size, 1.0f / m_steps_per_interval);
}
