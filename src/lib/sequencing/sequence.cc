#include "sequence.hh"

Sequence::Note::Note
(
    double start_point,
    double end_point,
    double steps,
    double velocity
) : m_start_point(start_point),
    m_end_point(end_point),
    m_steps(steps),
    m_velocity(velocity)
{

}

Sequence::Pattern::Pattern()
{
}

void Sequence::Pattern::add_note(Note note)
{
    m_notes.push_back(note);
}

std::vector<Sequence::Note> Sequence::Pattern::notes() const
{
    return m_notes;
}

Sequence::Sequence()
    : m_instrument(nullptr),
      m_tuning(nullptr)
{

}

Audio_data::Sample Sequence::get_sample(float frequency, Offset offset) const
{
    if(m_instrument && m_tuning)
    {
        return m_instrument->get_sample(frequency, offset);
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

Sequence::Pattern & Sequence::pattern()
{
    return m_pattern;
}









