#pragma once

#include <memory>

#include "effect.hh"

class Effect_stack
{
  public:
    Effect_stack();
    void add_effect(std::shared_ptr<Effect> effect);
    Audio_data::Sample get_sample
    (
        Audio_source const & source,
        float frequency,
        Audio_source::Offset offset
    ) const;
    double linger_time() const;
  private:
    std::vector<std::shared_ptr<Effect>> m_effects;
};
