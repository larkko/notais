#pragma once

#include <QWidget>

#include "keyboard.hh"

class Keyboard_widget : public QWidget
{
  public:
    Keyboard_widget(Keyboard & keyboard, QWidget * parent = nullptr);
  private:
    Keyboard & m_keyboard;
};