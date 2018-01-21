#pragma once

#include <memory>

#include <RtAudio.h>

class Audio_output
{
  public:
    Audio_output();
    void start();
    void stop();
  private:
    RtAudio m_out;
};