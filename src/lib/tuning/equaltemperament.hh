#pragma once

#include "tuning.hh"

class Equal_temperament : public Tuning
{
  public:
    Equal_temperament
    (
        float steps_per_interval,
        float interval_size,
        float base_frequency
    );
    float frequency_at(float steps) const override;
    float steps_per_interval() const;
    void set_steps_per_interval(float value);
    float interval_size() const;
    void set_interval_size(float value);
    float base_frequency() const;
    void set_base_frequency(float value);
  private:
    float step_multiplier() const;
    float m_steps_per_interval;
    float m_interval_size;
    float m_base_frequency;
};
