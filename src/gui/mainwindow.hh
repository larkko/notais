#pragma once

#include <QWidget>
#include <RtMidi.h>

class Main_window : public QWidget
{
  Q_OBJECT
  public:
    Main_window();
  private:
    RtMidiIn m_midi_in;
};