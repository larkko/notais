#pragma once

#include <vector>
#include <memory>

#include "../audio/adjustableaudiosource.hh"
#include "../tuning/tuning.hh"

class Project
{
  public:
    void add_instrument
    (
        std::shared_ptr<Adjustable_audio_source> const & instrument
    );
    std::vector<std::shared_ptr<Adjustable_audio_source>> const & 
    instruments() const;
    void add_tuning(std::shared_ptr<Tuning> const tuning);
    std::vector<std::shared_ptr<Tuning>> const & tunings() const;
  private:
    std::vector<std::shared_ptr<Adjustable_audio_source>> m_instruments;
    std::vector<std::shared_ptr<Tuning>> m_tunings;
};