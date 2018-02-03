#pragma once

#include <vector>
#include <memory>

#include "../audio/adjustableaudiosource.hh"
#include "../tuning/tuning.hh"

class Project
{
  public:
  private:
    std::vector<std::shared_ptr<Adjustable_audio_source>> m_instruments;
    std::vector<std::shared_ptr<Tuning>> m_tunings;
};