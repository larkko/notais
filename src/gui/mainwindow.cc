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
                if(!m_audio_out.is_active())
                {
                    m_audio_out.start();
                }
            }
            else
            {
                m_keyboard.set(e.key, 0.0f);
                if(m_audio_out.is_active() && !m_keyboard.is_active())
                {
                    m_audio_out.stop();
                }
            }
        }
    ))
{
}