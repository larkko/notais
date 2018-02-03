#include "projectwidget.hh"

#include <QLabel>
#include <QHBoxLayout>

Project_widget::Project_widget()
{
    QHBoxLayout * root_layout = new QHBoxLayout();

    QVBoxLayout * instrument_side_layout = new QVBoxLayout();
    QLabel * instruments_label = new QLabel();
    instruments_label->setText("Instruments");
    instruments_label->setAlignment(Qt::AlignHCenter);
    QFont label_font = instruments_label->font();
    label_font.setPointSize(13);
    label_font.setBold(true);
    instruments_label->setFont(label_font);
    instrument_side_layout->addWidget(instruments_label);
    m_instrument_list_layout = new QVBoxLayout();
    instrument_side_layout->addLayout(m_instrument_list_layout);

    QVBoxLayout * tuning_side_layout = new QVBoxLayout();
    QLabel * tunings_label = new QLabel();
    tunings_label->setText("Tunings");
    tunings_label->setAlignment(Qt::AlignHCenter);
    tunings_label->setFont(label_font);
    tuning_side_layout->addWidget(tunings_label);
    m_tuning_list_layout = new QVBoxLayout();
    tuning_side_layout->addLayout(m_tuning_list_layout);

    root_layout->addLayout(instrument_side_layout);
    root_layout->addLayout(tuning_side_layout);

    this->setLayout(root_layout);
}