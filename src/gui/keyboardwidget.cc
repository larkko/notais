#include <iostream>

#include <QLabel>
#include <QPainter>
#include <cmath>

#include "keyboardwidget.hh"

Keyboard_widget::Keyboard_widget(Keyboard & keyboard, QWidget * parent)
    : QWidget(parent),
      m_keyboard(keyboard)
{
}

void Keyboard_widget::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    for(size_t i = 0; i < m_keyboard.key_count(); ++i)
    {
        Qt::GlobalColor color = m_keyboard.key_is_active(i)
                              ? Qt::cyan
                              : Qt::darkGray;
        float width = (float)(this->width()) / (float)(m_keyboard.key_count());
        int height = this->height();
        int x = floor(i * width);
        painter.fillRect(x, 0, ceil(width), height, color);
    }
}