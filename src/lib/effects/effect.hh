#pragma once

#include "../audio/audiosource.hh"

class Effect
{
  public:
    virtual ~Effect();
    virtual Audio_data::Sample get_sample
    (
        Audio_source const & source,
        float frequency,
        Audio_source::Offset offset
    ) const = 0;
    virtual double linger_time() const = 0;
};
