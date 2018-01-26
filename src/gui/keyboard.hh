#pragma once

#include <array>
#include <cstddef>
#include <chrono>

class Keyboard
{
  public:
    Keyboard();

    struct Keypress
    {
        Keypress(float velocity = 0.0f, size_t elapsed_time = 0);
        float velocity;
        size_t elapsed_time;
    };

    Keypress at(int key);
    void set(int key, Keypress press);
    bool is_active();
    bool key_is_active(int key);
    size_t key_count();
    void advance_time(size_t amount);
  private:
    bool contains(int key);
    /*The number of keys in possible to express in a MIDI message
      can be used as our keyboard size here.*/
    static constexpr int m_size = 128;
    std::array<Keypress, m_size> m_keys;
};