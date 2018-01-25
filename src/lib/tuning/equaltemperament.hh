#pragma once

#include "tuning.hh"

class Equal_temperament : public Tuning
{
  public:
    Equal_temperament(float steps_per_interval,
                      float interval_size,
                      float base_frequency);
    float frequency_at(float steps) const override;
  private:
    float step_multiplier() const;
    float m_steps_per_interval;
    float m_interval_size;
    float m_base_frequency;
};
