#pragma once

#include <array>
#include <cstddef>

class Keyboard
{
  public:
    Keyboard();

    struct Keypress
    {
        Keypress(float velocity = 0.0f);
        float velocity;
    };

    Keypress at(int key);
    void set(int key, Keypress press);
    bool is_active();
    bool key_is_active(int key);
    size_t size();
  private:
    bool contains(int key);
    /*The number of keys in possible to express in a MIDI message
      can be used as our keyboard size here.*/
    static constexpr int m_size = 128;
    std::array<Keypress, m_size> m_keys;
};