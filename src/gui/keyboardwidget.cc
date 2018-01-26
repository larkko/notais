#include <iostream>

#include <QLabel>
#include <QPainter>
#include <cmath>

#include "keyboardwidget.hh"

Keyboard_widget::Keyboard_widget(Keyboard & keyboard, QWidget * parent)
    : QWidget(parent),
      m_keyboard(keyboard),
      m_held_key(-1)
{
}

QRect Keyboard_widget::key_rect(int key)
{
    int width = ceil((float)(this->width()) / (float)(m_keyboard.key_count()));
    int height = this->height();
    int x = floor(key * width);
    int y = 0;
    return QRect(x, y, width, height);
}

void Keyboard_widget::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    for(size_t key = 0; key < m_keyboard.key_count(); ++key)
    {
        /*Draw keys*/
        Qt::GlobalColor color = m_keyboard.key_is_active(key)
                              ? Qt::cyan
                              : Qt::darkGray;
        QRect rect = key_rect(key);
        painter.fillRect(rect, color);
        /*Draw separator between keys*/
        Qt::GlobalColor separator_color = Qt::black;
        painter.setPen(separator_color);
        painter.drawLine(rect.topLeft(), rect.bottomLeft());
    }
}

int Keyboard_widget::key_at(QPoint location)
{
    for(size_t key = 0; key < m_keyboard.key_count(); ++key)
    {
        QRect rect = key_rect(key);
        if(location.x() >= rect.x() && location.x() < (rect.x() + rect.width()))
        {
            return key;
        }
    }
    return -1;
}

void Keyboard_widget::mousePressEvent(QMouseEvent * event)
{
    int key = key_at(event->pos());
    if(key >= 0)
    {
        if(m_keyboard.key_is_active(key))
        {
            m_keyboard.set(key, Keyboard::Keypress(0.0f));
        }
        else
        {
            m_keyboard.set(key, Keyboard::Keypress(1.0f));
        }
        update();
    }
    m_held_key = key;
}

void Keyboard_widget::mouseReleaseEvent(QMouseEvent * event)
{
    if(m_held_key >= 0)
    {
        m_keyboard.set(m_held_key, Keyboard::Keypress(0.0f));
        m_held_key = -1;
        update();
    }
}





