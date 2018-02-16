#include "headingwidget.hh"

Heading_widget::Heading_widget(std::string const & text, QWidget * parent)
    : QLabel(QString::fromStdString(text), parent)
{
    setAlignment(Qt::AlignHCenter);
    QFont label_font = font();
    label_font.setPointSize(13);
    label_font.setBold(true);
    setFont(label_font);
}