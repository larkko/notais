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
    void get_samples
    (
        Audio_data & destination,
        float frequency,
        float volume,
        size_t sample_count,
        size_t offset_in_source,
        size_t offset_in_destination
    ) const override;
  private:
    Type m_type;
};