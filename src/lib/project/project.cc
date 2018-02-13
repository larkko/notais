#include "project.hh"


void Project::add_instrument
(
    std::shared_ptr<Adjustable_audio_source> const & instrument
)
{
    m_instruments.push_back(instrument);
}

std::vector<std::shared_ptr<Adjustable_audio_source>> const &
Project::instruments() const
{
    return m_instruments;
}

void Project::add_tuning(std::shared_ptr<Tuning> const tuning)
{
    m_tunings.push_back(tuning);
}

std::vector<std::shared_ptr<Tuning>> const & Project::tunings() const
{
    return m_tunings;
}
