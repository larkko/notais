#include "tuninglistwidget.hh"

#include <QLabel>

Tuning_list_widget::Tuning_list_widget()
{
    QVBoxLayout * layout = new QVBoxLayout();
    QLabel * label = new QLabel("tuning list widget");
    layout->addWidget(label);
    this->setLayout(layout);
}