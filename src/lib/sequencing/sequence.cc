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

double Sequence::Note::start_point() const
{
    return m_start_point;
}

double Sequence::Note::end_point() const
{
    return m_end_point;
}

double Sequence::Note::steps() const
{
    return m_steps;
}

double Sequence::Note::velocity() const
{
    return m_velocity;
}

double Sequence::Note::length() const
{
    return end_point() - start_point();
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

bool Sequence::contains(Audio_source const & other) const
{
    return (this == &other) || 
           ((m_instrument)
               ? (m_instrument->contains(other))
               : false); 
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









