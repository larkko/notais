#pragma once

#include <vector>
#include <functional>
#include <memory>

namespace MIDI
{

struct Event
{
    bool down;
    int key;
    float velocity;
    template <typename Sequence>
    static Event from(Sequence sequence);
};

class Input_implementation
{
  public:
    virtual ~Input_implementation() {}
    virtual bool open_port(char const * port) = 0;
    virtual bool run(std::function<void (Event)> callback) = 0;
};

/*A wrapper type for MIDI input*/
class Input
{
  public:
    Input(std::function<void (Event)> callback);
    std::function<void (Event)> const callback;
  private:
    std::unique_ptr<Input_implementation> m_implementation;
};


template <typename Sequence>
Event Event::from(Sequence sequence)
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

}
