#pragma once

#include <chrono>

#include <QWidget>

#include "midiinput.hh"
#include "keyboard.hh"
#include "keyboardwidget.hh"
#include "audiooutput.hh"
#include "../lib/audio/adjustableaudiosource.hh"
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
    std::shared_ptr<Adjustable_audio_source> m_active_instrument;
    std::shared_ptr<Tuning> m_active_tuning;
    std::chrono::steady_clock::time_point m_last_activity;
  signals:
    void keyboard_state_changed();
};
