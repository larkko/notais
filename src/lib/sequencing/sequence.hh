#pragma once

#include "../audio/adjustableaudiosource.hh"
#include "../tuning/tuning.hh"

class Sequence : public Audio_source
{
  public:
    Sequence();
    virtual Audio_data::Sample get_sample
    (
        float frequency,
        Offset offset
    ) const final override;
    virtual double linger_time() const final override;
    void set_instrument(std::shared_ptr<Adjustable_audio_source> instrument);
    void set_tuning(std::shared_ptr<Tuning> tuning);
  private:
    std::shared_ptr<Adjustable_audio_source> m_instrument;
    std::shared_ptr<Tuning> m_tuning;
};
