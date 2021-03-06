#pragma once

#include "effect.hh"

class Envelope : public Effect
{
  public:
    Envelope(double attack_length, double release_length);
    virtual Audio_data::Sample get_sample
    (
        Audio_source const & source,
        float frequency,
        Audio_source::Offset offset
    ) const final override;
    virtual double linger_time() const final override;
    double attack_length() const;
    void set_attack_length(double length);
    double release_length() const;
    void set_release_length(double length);
  private:
    float volume_at(Audio_source::Offset offset) const;
    double m_attack_length;
    double m_release_length;
};
