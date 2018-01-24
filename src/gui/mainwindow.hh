#pragma once

#include <QWidget>

#include "midiinput.hh"
#include "keyboard.hh"
#include "audiooutput.hh"
#include "../lib/audio/audiosource.hh"

class Main_window : public QWidget
{
  Q_OBJECT
  public:
    Main_window();
  private:
    MIDI_input m_midi_input;
    Keyboard m_keyboard;
    Audio_output m_audio_out;
};