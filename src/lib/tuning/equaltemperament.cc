#include "equaltemperament.hh"
#include <cmath>

Equal_temperament::Equal_temperament
(
    float steps_per_interval,
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

float Equal_temperament::step_multiplier() const
{
    return pow(m_interval_size, 1.0f / m_steps_per_interval);
}
