#include <iostream>
#include <math.h>

#include "mainwindow.hh"
#include "../lib/audio/oscillator.hh"

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
    )),
    m_audio_out(Audio_output
    (
        [&](Audio_data & destination)
        {
            for(int key = 0; key < m_keyboard.size(); ++key)
            {
                if(m_keyboard.key_is_active(key))
                {
                    m_active_instrument->get_samples
                    (
                        destination,
                        440.0f, //frequency
                        m_keyboard.at(key), //volume
                        destination.frame_count(),
                        0, //source offset
                        0 //destination offset
                    );
                }
            }
        }
    )),
    m_active_instrument
    (
        std::make_unique<Oscillator>(Oscillator(Oscillator::Type::Sine))
    )
{
}