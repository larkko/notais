#include "projectwidget.hh"

#include <QLabel>
#include <QHBoxLayout>

#include "instrumentlistwidget.hh"
#include "tuninglistwidget.hh"
#include "headingwidget.hh"
#include "taskqueue.hh"

Project_widget::Project_widget(Task_queue & task_queue)
    : m_project(Project()),
      m_task_queue(task_queue)
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
    Tuning_list_widget * tuning_list = new Tuning_list_widget(m_task_queue);
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

    QObject::connect
    (
        this,
        &Project_widget::instruments_updated,
        instrument_list,
        &Instrument_list_widget::update_list
    );

    QObject::connect
    (
        instrument_list,
        &Instrument_list_widget::selected,
        this,
        &Project_widget::instrument_selected
    );

    QObject::connect
    (
        tuning_list,
        &Tuning_list_widget::add_tuning,
        this,
        &Project_widget::add_tuning
    );

    QObject::connect
    (
        this,
        &Project_widget::tunings_updated,
        tuning_list,
        &Tuning_list_widget::update_list
    );

    QObject::connect
    (
        tuning_list,
        &Tuning_list_widget::selected,
        this,
        &Project_widget::tuning_selected
    );    
}

void Project_widget::add_instrument
(
    std::shared_ptr<Adjustable_audio_source> instrument
)
{
    atomic_perform
    (
        m_task_queue,
        [&, instrument]()
        {
            m_project.add_instrument(instrument);
        }
    );
    emit instruments_updated(m_project.instruments());
}

void Project_widget::add_tuning(std::shared_ptr<Tuning> tuning)
{
    atomic_perform
    (
        m_task_queue,
        [&, tuning]()
        {
            m_project.add_tuning(tuning);
        }
    );
    emit tunings_updated(m_project.tunings());
}


