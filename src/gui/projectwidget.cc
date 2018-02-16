#include "projectwidget.hh"

#include <QLabel>
#include <QHBoxLayout>

#include "instrumentlistwidget.hh"
#include "tuninglistwidget.hh"

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
    Instrument_list_widget * instrument_list = new Instrument_list_widget();
    instrument_side_layout->addWidget(instrument_list);

    QVBoxLayout * tuning_side_layout = new QVBoxLayout();
    QLabel * tunings_label = new QLabel();
    tunings_label->setText("Tunings");
    tunings_label->setAlignment(Qt::AlignHCenter);
    tunings_label->setFont(label_font);
    tuning_side_layout->addWidget(tunings_label);
    Tuning_list_widget * tuning_list = new Tuning_list_widget();
    tuning_side_layout->addWidget(tuning_list); 

    root_layout->addLayout(instrument_side_layout);
    root_layout->addLayout(tuning_side_layout);

    this->setLayout(root_layout);
}