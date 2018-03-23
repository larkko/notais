#include "sequence.hh"

Sequence::Sequence()
    : m_instrument(nullptr),
      m_tuning(nullptr)
{

}

Audio_data::Sample Sequence::get_sample(float frequency, Offset offset) const
{
    if(m_instrument && m_tuning)
    {
        return 0;
    }
    else
    {
        return 0;
    }
}

double Sequence::linger_time() const
{
    if(m_instrument)
    {
        return m_instrument->linger_time();
    }
    else
    {
        return 0;
    }
}

void Sequence::set_instrument
(
    std::shared_ptr<Adjustable_audio_source> instrument
)
{
    m_instrument = instrument;
}

void Sequence::set_tuning(std::shared_ptr<Tuning> tuning)
{
    m_tuning = tuning;
}











