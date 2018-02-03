#include "keyboard.hh"

Keyboard::Keyboard(int offset)
    : m_keys(std::array<Keyboard::Keypress, m_size>()),
      m_offset(offset)
{
}

Keyboard::Keypress::Keypress(float velocity, size_t elapsed_time)
    : velocity(velocity),
      elapsed_time(elapsed_time)
{
}

void Keyboard::press(Key key, float velocity)
{
    if(contains(key))
    {
        int index = raw_index(key);
        m_keys[index] = Keypress(velocity);
    }
}

void Keyboard::release(Key key)
{
    if(contains(key))
    {
        int index = raw_index(key);
        m_keys[index] = Keypress();
    }
}

bool Keyboard::is_active() const
{
    bool active = false;
    for(Keyboard::Keypress press : m_keys)
    {
        if(press.velocity != 0.0f)
        {
            active = true;
        }
    }
    return active;
}

bool Keyboard::key_is_active(Key key) const
{
    int index = raw_index(key);
    return contains(key) && m_keys[index].velocity > 0.0f;
}

size_t Keyboard::key_count() const
{
    return m_keys.size();
}

void Keyboard::advance_time(size_t amount)
{
    for(Keyboard::Keypress & press : m_keys)
    {
        press.elapsed_time += amount;
    }
}

bool Keyboard::contains(Key key) const
{
    int index = raw_index(key);
    return index >= 0 && index < int(key_count());
}

int Keyboard::raw_index(Key key) const
{
    return (key.type == Key::Type::Raw)
            ? key.key
            : key.key + m_offset;
}

int Keyboard::offset_index(Key key) const
{
    return (key.type == Key::Type::Offset)
            ? key.key
            : key.key - m_offset;
}
















