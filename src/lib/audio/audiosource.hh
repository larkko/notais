#pragma once

#include "audiodata.hh"

class Audio_source
{
  public:
    virtual ~Audio_source(){};
    virtual void get_samples
    (
        Audio_data & destination,
        float frequency,
        size_t sample_count,
        size_t offset_in_source,
        size_t offset_in_destination
    ) const = 0;
};