#pragma once

#include <vector>

#include <RtMidi.h>

/*A wrapper type for MIDI input*/
class MIDI_input
{
  public:

    struct Event
    {
        bool down;
        int key;
        float velocity;
    };

    MIDI_input();
  private:
    /*Provides a far less cryptic representation of the relevant
      MIDI message.*/
    Event as_event(std::vector<unsigned char> * message);

    RtMidiIn m_midi_in;
};