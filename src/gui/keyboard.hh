#pragma once

#include <array>
#include <cstddef>
#include <chrono>

class Keyboard
{
  public:
    Keyboard();

    struct Key
    {
        enum class Type
        {
            Offset,
            Raw
        };
        int key;
        Type type;
    };

    struct Keypress
    {
        Keypress(float velocity = 0.0f, size_t elapsed_time = 0);
        float velocity;
        size_t elapsed_time;
    };

    /*Performs function for each keypress, with a keypress and key (int) as its
      parameters. Whether offset is applied to key depends on the type.*/
    template<typename F>
    void for_each(F function, Key::Type type);
    void press(int key, float velocity);
    void release(int key);
    bool is_active() const;
    bool key_is_active(int key) const;
    size_t key_count() const;
    void advance_time(size_t amount);
  private:
    bool contains(int key) const;
    /*The number of keys in possible to express in a MIDI message
      can be used as our keyboard size here.*/
    static constexpr int m_size = 128;
    std::array<Keypress, m_size> m_keys;
};


template<typename F>
void Keyboard::for_each(F function, Key::Type type)
{
    for(int key = 0; key < int(key_count()); ++key)
    {
        function(m_keys[key], key);
    }
}