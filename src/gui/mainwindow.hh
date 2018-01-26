#pragma once

#include <QWidget>

#include "midiinput.hh"
#include "keyboard.hh"
#include "keyboardwidget.hh"
#include "audiooutput.hh"
#include "../lib/audio/audiosource.hh"
#include "../lib/tuning/tuning.hh"

class Main_window : public QWidget
{
  Q_OBJECT
  public:
    Main_window();
  private:
    void update_audio_state();
    MIDI_input m_midi_input;
    Keyboard m_keyboard;
    Audio_output m_audio_out;
    std::unique_ptr<Audio_source> m_active_instrument;
    std::unique_ptr<Tuning> m_active_tuning;
    Keyboard_widget * m_keyboard_widget;
  signals:
    void keyboard_state_changed();
};