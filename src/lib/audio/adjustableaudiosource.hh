#pragma once

#include <memory>

#include "audiosource.hh"

class Adjustable_audio_source : public Audio_source
{
  public:
    Adjustable_audio_source
    (
        std::shared_ptr<Audio_source> const & audio_source
    );
    virtual Audio_data::Sample get_sample
    (
        float frequency,
        double offset
    ) const override;
  private:
    std::shared_ptr<Audio_source> m_audio_source;
};