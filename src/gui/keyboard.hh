#pragma once

#include <array>

class Keyboard
{
  public:
    Keyboard();
    float at(int key);
    void set(int key, float value);
    bool is_active();
  private:
    bool contains(int key);
    /*The number of keys in possible to express in a MIDI message
      can be used as our keyboard size here.*/
    static constexpr int size = 128;
    std::array<float, size> m_keys;
};