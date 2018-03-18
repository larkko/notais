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

double Adjustable_audio_source::linger_time() const
{
    return m_audio_source->linger_time() + m_effect_stack.linger_time();
}

std::shared_ptr<Audio_source> & Adjustable_audio_source::audio_source()
{
    return m_audio_source;
}

Effect_stack & Adjustable_audio_source::effect_stack()
{
    return m_effect_stack;
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
