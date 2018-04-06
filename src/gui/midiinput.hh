#pragma once

#include <vector>
#include <functional>

#include <../3rdparty/rtmidi/RtMidi.h>

/*A wrapper type for MIDI input*/
class MIDI_input
{
  public:
    /*Provides a far less cryptic representation of a MIDI message.*/
    struct Event
    {
        bool down;
        int key;
        float velocity;
    };

    MIDI_input(std::function<void (Event)> callback);

    std::function<void (Event)> const callback;

  private:
    /*Provides the corresponding event struct for the given MIDI message.*/
    Event as_event(std::vector<unsigned char> * message) const;

    RtMidiIn m_midi_in;
};
