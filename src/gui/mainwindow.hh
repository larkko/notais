#pragma once

#include <QWidget>
#include <QTimer>

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
    void start_audio_stop_timer();
    MIDI_input m_midi_input;
    Keyboard m_keyboard;
    Audio_output m_audio_out;
    QTimer * m_audio_stop_timer;
    std::shared_ptr<Adjustable_audio_source> m_active_instrument;
    std::shared_ptr<Tuning> m_active_tuning;
  signals:
    void keyboard_state_changed();
};
