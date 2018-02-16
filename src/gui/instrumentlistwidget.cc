#include "instrumentlistwidget.hh"

#include <QLabel>

Instrument_list_widget::Instrument_list_widget()
{
    QVBoxLayout * layout = new QVBoxLayout();
    QLabel * label = new QLabel("instrument list widget");
    layout->addWidget(label);
    this->setLayout(layout);
}