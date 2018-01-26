#pragma once

#include <QWidget>
#include <QRect>
#include <QMouseEvent>

#include "keyboard.hh"

class Keyboard_widget : public QWidget
{
  Q_OBJECT
  public:
    Keyboard_widget(Keyboard & keyboard, QWidget * parent = nullptr);
  private:
    QRect key_rect(int key);
    void paintEvent(QPaintEvent * event) override;
    int key_at(QPoint location);
    void mousePressEvent(QMouseEvent * event) override;
    void mouseReleaseEvent(QMouseEvent * event) override;
    Keyboard & m_keyboard;
    int m_held_key;
  signals:
    void keyboard_state_changed();
};