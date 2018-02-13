#pragma once

#include "audiosource.hh"

class Oscillator : public Audio_source
{
  public:
    enum class Type
    {
        Sine,
        Square,
        Saw
    };
    Oscillator(Type type);
    Audio_data::Sample get_sample
    (
        float frequency,
        double offset
    ) const final override;
  private:
    Type m_type;
};