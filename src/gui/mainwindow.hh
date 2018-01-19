#pragma once

#include <QWidget>

#include "midiinput.hh"

class Main_window : public QWidget
{
  Q_OBJECT
  public:
    Main_window();
  private:
    MIDI_input m_midi_input;
};