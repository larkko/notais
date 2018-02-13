#pragma once

#include "audiodata.hh"

class Audio_source
{
  public:
    virtual ~Audio_source(){};
    virtual Audio_data::Sample get_sample
    (
        float frequency,
        double offset
    ) const = 0;
    void get_samples
    (
        Audio_data & destination,
        float frequency,
        float volume,
        size_t sample_count,
        size_t offset_in_source,
        size_t offset_in_destination
    ) const;
};