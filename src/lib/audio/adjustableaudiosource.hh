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
    ) const final override;
    virtual double linger_time() const final override;
    virtual bool contains(Audio_source const & other) const final override;
    virtual std::string description() const final override;
    std::shared_ptr<Audio_source> & audio_source();
    Effect_stack & effect_stack();
    float volume() const;
    void set_volume(float value);
    std::string const & name() const;
  private:
    std::shared_ptr<Audio_source> m_audio_source;
    Effect_stack m_effect_stack;
    float m_volume;
    std::string m_name;
};
