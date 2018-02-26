#pragma once

#include <array>
#include <cstddef>
#include <chrono>

class Keyboard
{
  public:
    Keyboard(int offset = 0);

    typedef int Key_identifier;

    struct Key
    {
        enum class Type
        {
            Offset,
            Raw
        };
        Key_identifier key;
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
    void press(Key key, float velocity);
    void release(Key key);
    bool is_active() const;
    bool key_is_active(Key key) const;
    size_t key_count() const;
    void advance_time(size_t amount);
  private:
    bool contains(Key key) const;
    int raw_index(Key key) const;
    int offset_index(Key key) const;
    /*The number of keys in possible to express in a MIDI message
      can be used as our keyboard size here.*/
    static constexpr int m_size = 128;
    std::array<Keypress, m_size> m_keys;
    int m_offset;
};

#include "keyboard.tt"



















