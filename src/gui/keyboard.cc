#include "keyboard.hh"

Keyboard::Keyboard(int offset, size_t history_size)
    : m_offset(offset)
{
    for(size_t i = 0; i < history_size; ++i)
    {
        m_presses.push_back(Keyboard::Keypress());
    }
}

Keyboard::Keypress::Keypress
(
    Key_identifier key,
    float velocity,
    size_t elapsed_time,
    size_t release_offset,
    bool expired
)
    : key(key),
      velocity(velocity),
      elapsed_time(elapsed_time),
      release_offset(release_offset),
      expired(expired)
{
}

Keyboard::Keypress::State Keyboard::Keypress::state() const
{
    if(expired)
    {
        return State::Expired;
    }
    else
    {
        if(release_offset == 0)
        {
            return State::Pressed;
        }
        else
        {
            return State::Released;
        }
    }
}

size_t Keyboard::Keypress::time_since_release() const
{
    return (state() == State::Pressed) ? 0 : (elapsed_time - release_offset);
}

void Keyboard::press(Key key, float velocity)
{
    auto raw_id = raw_key_identifier(key);
    for(Keypress & press : m_presses)
    {
        if(press.state() == Keypress::State::Expired)
        {
            Keypress result(raw_id, velocity, 0, 0, false);
            press = result;
            break;
        }
    }
}

void Keyboard::release(Key key)
{
    for(Keypress & press : m_presses)
    {
        if(press.key == raw_key_identifier(key) &&
           press.state() == Keypress::State::Pressed)
        {
            press.release_offset = press.elapsed_time;
        }
    }
}

void Keyboard::expire(Keyboard::Press_identifier press)
{
    if(press < m_presses.size())
    {
        m_presses[press].expired = true;
    }
}

bool Keyboard::is_active() const
{
    bool active = false;
    for(Keypress const & press : m_presses)
    {
        if(!press.expired &&
           press.state() == Keypress::State::Pressed)
        {
            active = true;
        }
    }
    return active;
}

bool Keyboard::key_is_active(Key key, bool include_released) const
{
    bool active = false;
    for(Keypress const & press : m_presses)
    {
        bool key_active = press.state() == Keypress::State::Pressed
                        || (press.state() == Keypress::State::Released
                            && include_released);
        if(!press.expired &&
           key_active &&
           press.key == raw_key_identifier(key))
        {
            active = true;
        }
    }
    return active;
}

size_t Keyboard::key_count() const
{
    size_t const MIDI_key_count = 128;
    return MIDI_key_count;
}

void Keyboard::advance_time(size_t amount)
{
    for(Keypress & press : m_presses)
    {
        if(!press.expired)
        {
            press.elapsed_time += amount;
        }
    }
}

int Keyboard::raw_key_identifier(Key key) const
{
    return (key.type == Key::Type::Raw)
            ? key.key
            : (key.key + m_offset);
}

int Keyboard::offset_key_identifier(Key key) const
{
    return (key.type == Key::Type::Offset)
            ? key.key
            : (key.key - m_offset);
}
















