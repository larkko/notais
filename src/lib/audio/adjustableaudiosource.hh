#pragma once

#include "audiosource.hh"

class Adjustable_audio_source : public Audio_source
{
  public:
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
};