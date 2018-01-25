#include "keyboard.hh"

Keyboard::Keyboard()
    : m_keys(std::array<Keyboard::Keypress, m_size>())
{
}

Keyboard::Keypress::Keypress(float velocity, size_t elapsed_time)
    : velocity(velocity),
      elapsed_time(elapsed_time)
{
}

Keyboard::Keypress Keyboard::at(int key)
{
    return contains(key) ? m_keys[key] : Keyboard::Keypress(0.0f);
}

void Keyboard::set(int key, Keyboard::Keypress press)
{
    if(contains(key))
    {
        m_keys[key] = press;
    }
}

bool Keyboard::is_active()
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

bool Keyboard::key_is_active(int key)
{
    return contains(key) && m_keys[key].velocity > 0.0f;
}

size_t Keyboard::size()
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

bool Keyboard::contains(int key)
{
    return key >= 0 && key < static_cast<int>(size());
}