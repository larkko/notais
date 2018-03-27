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

std::vector<Sequence::Note> const & Sequence::Pattern::notes() const
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
    (void)frequency;
    
    if(m_instrument && m_tuning)
    {
        auto linger_time = m_instrument->linger_time();
        Audio_data::Sample sample = 0;
        for(auto & note : m_pattern.notes())
        {
            if((offset.offset() >= note.start_point())
               && (offset.offset() <= (note.end_point() + linger_time)))
            {
                auto note_local_start =  offset.offset() - note.start_point();
                bool released = note.end_point() > offset.offset();
                auto note_local_release =  offset.offset() - note.end_point();
                Offset note_local_offset = released
                                         ? Offset
                                           (
                                                note_local_start,
                                                note_local_release
                                           )
                                         : Offset(note_local_start);
                auto note_frequency = m_tuning->frequency_at(note.steps());
                sample += m_instrument->get_sample(note_frequency, note_local_offset);
            }
        }
        return sample;
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









