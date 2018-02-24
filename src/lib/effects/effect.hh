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
        double offset
    ) const = 0;
};
