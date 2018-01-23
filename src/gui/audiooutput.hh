#pragma once

#include <memory>

#include <RtAudio.h>

#include "../lib/audio/audiodata.hh"

class Audio_output
{
  public:
    Audio_output();
    void start();
    void stop();
    bool is_active();
  private:
    RtAudio m_out;
    bool m_active;
};