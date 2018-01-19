#include <iostream>

#include "mainwindow.hh"

Main_window::Main_window()
    : m_midi_input(MIDI_input([](MIDI_input::Event e){(void)e;}))
{
    
}