#include "keyboard.hh"

Keyboard::Keyboard()
    : m_keys(std::array<float, m_size>())
{
}

float Keyboard::at(int key)
{
    return contains(key) ? m_keys[key] : 0.0f;
}

void Keyboard::set(int key, float value)
{
    if(contains(key))
    {
        m_keys[key] = value;
    }
}

bool Keyboard::is_active()
{
    bool active = false;
    for(float velocity : m_keys)
    {
        if(velocity != 0.0f)
        {
            active = true;
        }
    }
    return active;
}

bool Keyboard::key_is_active(int key)
{
    return contains(key) && m_keys[key] > 0.0f;
}

size_t Keyboard::size()
{
    return m_keys.size();
}

bool Keyboard::contains(int key)
{
    return key >= 0 && key < size();
}