#pragma once

#include <QWidget>
#include <QRect>
#include <QMouseEvent>

#include "keyboard.hh"

class Keyboard_widget : public QWidget
{
  Q_OBJECT
  public:
    Keyboard_widget(Keyboard const & keyboard, QWidget * parent = nullptr);

  private:
    QRect key_rect(int key) const;
    void paintEvent(QPaintEvent * event) override;
    int key_at(QPoint location) const;
    void mousePressEvent(QMouseEvent * event) override;
    void mouseReleaseEvent(QMouseEvent * event) override;
    QSize sizeHint() const override;
    Keyboard const & m_keyboard;
    int m_held_key;

    struct Pattern
    {
        int steps_per_pattern = 1;
        int offset = 0;
        bool valid = false;
        bool is_special(int key) const;
    };

    Pattern m_pattern;

  signals:
    void key_press_event(int key, float velocity);
    void key_release_event(int key);

  public slots:
    void change_pattern(int steps_per_pattern, int offset);
};
