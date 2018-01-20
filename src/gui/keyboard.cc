#include "keyboard.hh"

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

bool Keyboard::contains(int key)
{
    return key >= 0 && key < size;
}