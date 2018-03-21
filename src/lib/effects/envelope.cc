#include "envelope.hh"

Envelope::Envelope(double attack_length, double release_length)
    : m_attack_length(attack_length),
      m_release_length(release_length)
{

}

Audio_data::Sample Envelope::get_sample
(
    Audio_source const & source,
    float frequency,
    Audio_source::Offset offset
) const
{
    Audio_data::Sample sample = source.get_sample(frequency, offset);
    float volume = volume_at(offset);
    return volume * sample;
}

double Envelope::linger_time() const
{
    return m_release_length;
}

double Envelope::attack_length() const
{
    return m_attack_length;
}

void Envelope::set_attack_length(double length)
{
    m_attack_length = length;
}

double Envelope::release_length() const
{
    return m_release_length;
}

void Envelope::set_release_length(double length)
{
    m_release_length = length;
}

float Envelope::volume_at(Audio_source::Offset offset) const
{
    float volume = 0.0f;
    if(offset.released())
    {
        float peak = (offset.release_offset() > m_attack_length)
                   ? 1.0f
                   : (offset.release_offset() / m_attack_length);
        double elapsed = offset.time_since_release();
        volume = (elapsed > m_release_length)
               ? 0.0f
               : peak * (1.0f - (elapsed / m_release_length));
    }
    else
    {
        volume = (offset.offset() > m_attack_length)
               ? 1.0f
               : (offset.offset() / m_attack_length);
    }
    return volume;
}
