#pragma once

#include "audiosource.hh"

class Oscillator : public Audio_source
{
  public:
    enum class Type
    {
        Sine,
        Square,
        Saw,
        White_noise
    };
    Oscillator(Type type);
    virtual Audio_data::Sample get_sample
    (
        float frequency,
        Audio_source::Offset offset
    ) const final override;
    virtual std::string description() const final override;
    void set_type(Type type);
  private:
    Type m_type;
};
