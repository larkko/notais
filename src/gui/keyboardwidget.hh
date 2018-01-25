#pragma once

#include <QWidget>

#include "keyboard.hh"

class Keyboard_widget : public QWidget
{
  Q_OBJECT
  public:
    Keyboard_widget(Keyboard & keyboard, QWidget * parent = nullptr);
  private:
    void paintEvent(QPaintEvent * event) override;
    Keyboard & m_keyboard;
};