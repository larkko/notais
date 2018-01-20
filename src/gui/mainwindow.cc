#include <iostream>

#include "mainwindow.hh"

Main_window::Main_window()
    : m_midi_input(MIDI_input
    (
        [&](MIDI_input::Event e)
        {
            if(e.down)
            {
                m_keyboard.set(e.key, e.velocity);
            }
            else
            {
                m_keyboard.set(e.key, 0.0f);
            }
        }
    ))
{
    
}