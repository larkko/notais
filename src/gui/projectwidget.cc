#include "projectwidget.hh"

#include <QLabel>
#include <QHBoxLayout>

Project_widget::Project_widget()
{
    QHBoxLayout * root_layout = new QHBoxLayout();
    QLabel * label = new QLabel();
    label->setText("Project widget");
    root_layout->addWidget(label);
    this->setLayout(root_layout);
}