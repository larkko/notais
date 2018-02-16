#include "adjustableaudiosource.hh"

Adjustable_audio_source::Adjustable_audio_source
(
    std::shared_ptr<Audio_source> const & audio_source
)   : m_audio_source(audio_source)
{

}

Audio_data::Sample Adjustable_audio_source::get_sample
(
    float frequency,
    double offset
) const
{
    return m_audio_source->get_sample(frequency, offset);
}

std::shared_ptr<Audio_source> & Adjustable_audio_source::audio_source()
{
    return m_audio_source;
}

std::string const & Adjustable_audio_source::name() const
{
    return m_name;
}