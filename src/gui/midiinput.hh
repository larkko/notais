#pragma once

#include <RtMidi.h>

/*A wrapper type for MIDI input*/
class MIDI_input
{
  public:
    MIDI_input();
  private:
    RtMidiIn m_midi_in;
};