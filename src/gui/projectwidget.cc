#include "projectwidget.hh"

#include <QLabel>
#include <QHBoxLayout>

#include "instrumentlistwidget.hh"
#include "tuninglistwidget.hh"
#include "headingwidget.hh"

Project_widget::Project_widget()
    : m_project(Project())
{
    QHBoxLayout * root_layout = new QHBoxLayout();

    QVBoxLayout * instrument_side_layout = new QVBoxLayout();
    Heading_widget * instruments_label = new Heading_widget("Instruments");
    instrument_side_layout->addWidget(instruments_label);
    Instrument_list_widget * instrument_list = new Instrument_list_widget();
    instrument_side_layout->addWidget(instrument_list);

    QVBoxLayout * tuning_side_layout = new QVBoxLayout();
    Heading_widget * tunings_label = new Heading_widget("Tunings");
    tuning_side_layout->addWidget(tunings_label);
    Tuning_list_widget * tuning_list = new Tuning_list_widget();
    tuning_side_layout->addWidget(tuning_list); 

    root_layout->addLayout(instrument_side_layout);
    root_layout->addLayout(tuning_side_layout);

    this->setLayout(root_layout);

    QObject::connect
    (
        instrument_list,
        &Instrument_list_widget::add_instrument,
        this,
        &Project_widget::add_instrument
    );

}

void Project_widget::add_instrument
(
    std::shared_ptr<Adjustable_audio_source> instrument
)
{

}