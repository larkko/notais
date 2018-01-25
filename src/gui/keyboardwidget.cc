#include <QLabel>

#include "keyboardwidget.hh"

Keyboard_widget::Keyboard_widget(Keyboard & keyboard, QWidget * parent)
    : QWidget(parent),
      m_keyboard(keyboard)
{
    QLabel * label = new QLabel(this);
    label->setText("Keyboard widget");
}