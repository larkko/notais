#pragma once

#include <vector>
#include <cstddef>
#include <chrono>

class Keyboard
{
  public:
    Keyboard(int offset = 0, size_t history_size = 1000);

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

    typedef size_t Press_identifier;

    struct Keypress
    {
        Keypress
        (
            Key_identifier key = 0,
            float velocity = 0.0f,
            size_t elapsed_time = 0,
            size_t release_offset = 0,
            bool expired = true
        );
        Key_identifier key;
        float velocity;
        size_t elapsed_time;
        size_t release_offset;
        bool expired;

        enum class State
        {
            Pressed, Released, Expired
        };

        State state() const;

        size_t time_since_release() const;
    };

    /*Performs function for each keypress, with a keypress as its identifier
      parameters. Whether offset is applied to key depends on the type.*/
    template<typename F>
    void for_each(F function, Key::Type type);
    void press(Key key, float velocity);
    void release(Key key);
    void expire(Press_identifier press);
    bool is_active() const;
    bool key_is_active(Key key, bool include_released = false) const;
    size_t key_count() const;
    void advance_time(size_t amount);
  private:
    int raw_key_identifier(Key key) const;
    int offset_key_identifier(Key key) const;
    std::vector<Keypress> m_presses;
    int m_offset;
};


template<typename F>
void Keyboard::for_each(F function, Key::Type type)
{
    for(Press_identifier i = 0; i < m_presses.size(); ++i)
    {
        Keypress press = m_presses[i];
        if(!press.expired)
        {
            auto identifier = (type == Key::Type::Raw)
                            ? press.key
                            : offset_key_identifier({press.key, Key::Type::Raw});
            press.key = identifier;
            function(press, i);
        }
    }
}



















