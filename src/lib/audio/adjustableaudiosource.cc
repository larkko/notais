#include "adjustableaudiosource.hh"

Adjustable_audio_source::Adjustable_audio_source
(
    std::shared_ptr<Audio_source> const & audio_source
)   : m_audio_source(audio_source),
      m_volume(1.0f)
{

}

Audio_data::Sample Adjustable_audio_source::get_sample
(
    float frequency,
    Audio_source::Offset offset
) const
{
    return m_volume * m_effect_stack.get_sample(*m_audio_source, frequency, offset);
}

std::shared_ptr<Audio_source> & Adjustable_audio_source::audio_source()
{
    return m_audio_source;
}

float Adjustable_audio_source::volume() const
{
    return m_volume;
}

void Adjustable_audio_source::set_volume(float value)
{
    if(value >= 0.0f && value <= 1.0f)
    {
        m_volume = value;
    }
}

std::string const & Adjustable_audio_source::name() const
{
    return m_name;
}
