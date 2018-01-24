#pragma once

#include <array>
#include <cstddef>

class Keyboard
{
  public:
    Keyboard();
    float at(int key);
    void set(int key, float value);
    bool is_active();
    size_t size();
  private:
    bool contains(int key);
    /*The number of keys in possible to express in a MIDI message
      can be used as our keyboard size here.*/
    static constexpr int m_size = 128;
    std::array<float, m_size> m_keys;
};