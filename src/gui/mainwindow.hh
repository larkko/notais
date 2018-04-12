#pragma once

#include <QWidget>
#include <QTimer>

#include "midiinput.hh"
#include "keyboard.hh"
#include "keyboardwidget.hh"
#include "audiooutput.hh"
#include "taskqueue.hh"
#include "../lib/audio/adjustableaudiosource.hh"
#include "../lib/tuning/tuning.hh"

class Main_window : public QWidget
{
  Q_OBJECT
  public:
    Main_window();
  private:
    void update_audio_state();
    void use_instrument(Audio_data & audio_output_buffer);
    MIDI::Input m_midi_input;
    Keyboard m_keyboard;
    Audio_output m_audio_out;
    std::shared_ptr<Adjustable_audio_source const> m_active_instrument;
    std::shared_ptr<Tuning const> m_active_tuning;
    Task_queue m_project_tasks;
  signals:
    void keyboard_state_changed();
};
