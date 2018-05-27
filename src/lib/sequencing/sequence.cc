#include "sequence.hh"

#include <algorithm>

#include "../util/util.hh"

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

bool Sequence::Note::is_inside(util::Rectangle<double> rectangle) const
{
    return rectangle.contains
    (
        util::Line<double>
        (
            util::Point<double>(start_point(), steps()),
            util::Point<double>(end_point(), steps())
        )
    );
}

void Sequence::Note::lengthen_by(double amount, double minimum)
{
    m_end_point += amount;
    if(length() < minimum)
    {
        m_end_point = m_start_point + minimum;
    }
    if(length() < 0)
    {
        m_end_point = m_start_point;
    }
}

Sequence::Timing::Timing(double beats_per_minute)
    : m_beats_per_minute(beats_per_minute)
{
}

double Sequence::Timing::beats_per_minute() const
{
    return m_beats_per_minute;
}

void Sequence::Timing::set_beats_per_minute(double value)
{
    m_beats_per_minute = value;
}

double Sequence::Timing::to_seconds(double timepoint) const
{
    double ratio = 60.0 / m_beats_per_minute;
    return timepoint * ratio;
}

Sequence::Pattern::Pattern(Sequence::Timing timing)
    : m_timing(timing)
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

std::vector<Sequence::Pattern::Index> Sequence::Pattern::notes_within
(
    util::Rectangle<double> rectangle
) const
{
    std::vector<Index> result;
    
    for(Index i = 0; i < m_notes.size(); ++i)
    {
        if(m_notes[i].is_inside(rectangle))
        {
            result.push_back(i);
        }
    }
    
    return result;
}

void Sequence::Pattern::remove_notes(std::vector<Index> indices)
{
    std::vector<Note> remaining;
    
    for(Index i = 0; i < m_notes.size(); ++i)
    {
        if(std::find(indices.begin(), indices.end(), i) == indices.end())
        {
            remaining.push_back(m_notes[i]);
        }
    }
    
    m_notes = remaining;
}

Sequence::Timing const & Sequence::Pattern::timing() const
{
    return m_timing;
}

Sequence::Timing & Sequence::Pattern::timing()
{
    return m_timing;
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
        auto const & timing = pattern().timing();
        Audio_data::Sample sample = 0;
        for(auto & note : m_pattern.notes())
        {
            auto note_start = timing.to_seconds(note.start_point());
            auto note_end = timing.to_seconds(note.end_point());
            if((offset.offset() >= note_start)
               && (offset.offset() <= (note_end + linger_time)))
            {
                auto note_local_start =  offset.offset() - note_start;
                bool released = note_end > offset.offset();
                auto note_local_release =  offset.offset() - note_end;
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

std::string Sequence::description() const
{
    return "Sequence";
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

std::shared_ptr<Tuning> const & Sequence::tuning() const
{
    return m_tuning;
}

Sequence::Pattern & Sequence::pattern()
{
    return m_pattern;
}

Sequence::Pattern const & Sequence::pattern() const
{
    return m_pattern;
}

double Sequence::length() const
{
    double result = 0;
    for(auto & note : m_pattern.notes())
    {
        result = std::max(result, note.end_point());
    }
    result = (result > 0) ? result + linger_time() : result;
    return result;
}







