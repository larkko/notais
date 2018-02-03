#include "projectwidget.hh"

#include <QLabel>
#include <QHBoxLayout>

Project_widget::Project_widget()
{
    QHBoxLayout * root_layout = new QHBoxLayout();

    QVBoxLayout * instrument_side_layout = new QVBoxLayout();
    QLabel * instruments_label = new QLabel();
    instruments_label->setText("Instruments");
    instrument_side_layout->addWidget(instruments_label);
    m_instrument_list_layout = new QVBoxLayout();
    instrument_side_layout->addLayout(m_instrument_list_layout);

    QVBoxLayout * tuning_side_layout = new QVBoxLayout();
    QLabel * tunings_label = new QLabel();
    tunings_label->setText("Tunings");
    tuning_side_layout->addWidget(tunings_label);
    m_tuning_list_layout = new QVBoxLayout();
    tuning_side_layout->addLayout(m_tuning_list_layout);

    root_layout->addLayout(instrument_side_layout);
    root_layout->addLayout(tuning_side_layout);

    this->setLayout(root_layout);
}