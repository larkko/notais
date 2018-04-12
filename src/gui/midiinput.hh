#pragma once

#include <vector>
#include <functional>
#include <memory>

struct MIDI_event
{
    bool down;
    int key;
    float velocity;
    template <typename Sequence>
    static MIDI_event from(Sequence sequence);
};

class MIDI_input_implementation
{
  public:
    virtual ~MIDI_input_implementation() {}
    virtual bool open_port(char const * port) = 0;
    virtual bool run(std::function<void (MIDI_event)> callback) = 0;
};

/*A wrapper type for MIDI input*/
class MIDI_input
{
  public:
    MIDI_input(std::function<void (MIDI_event)> callback);
    std::function<void (MIDI_event)> const callback;
  private:
    std::unique_ptr<MIDI_input_implementation> m_implementation;
};


template <typename Sequence>
MIDI_event MIDI_event::from(Sequence sequence)
{
    if(sequence.size() >= 3)
    {
        /*MIDI "note on" event when first byte is 1001**** */
        bool down = (sequence[0] & 0b11110000) == 0b10010000;
        /*The key being struct is at byte number two*/
        int key = sequence[1];
        /*The velocity of the strike is the 7 least significant bits
          of the third byte (normalized to a float [0,1] here).*/
        float velocity = (float)(sequence[2]) / (float)0b01111111;
        return {down, key, velocity};
    }
    else
    {
        return {false, 0, 0.0f};
    }
}
