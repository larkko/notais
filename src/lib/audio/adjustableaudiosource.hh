#pragma once

#include <memory>

#include "audiosource.hh"
#include "../effects/effectstack.hh"

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
        Audio_source::Offset offset
    ) const override;
    std::shared_ptr<Audio_source> & audio_source();
    Effect_stack m_effect_stack;
    float volume() const;
    void set_volume(float value);
    std::string const & name() const;
  private:
    std::shared_ptr<Audio_source> m_audio_source;
    float m_volume;
    std::string m_name;
};
