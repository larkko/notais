#pragma once

#include "audiosource.hh"

class Adjustable_audio_source : public Audio_source
{
  public:
    virtual Audio_data::Sample get_sample
    (
        float frequency,
        double offset
    ) const override;
  private:
};