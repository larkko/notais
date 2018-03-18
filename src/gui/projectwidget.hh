#pragma once

#include <memory>

#include <QWidget>

#include "../lib/audio/adjustableaudiosource.hh"
#include "../lib/project/project.hh"
#include "taskqueue.hh"

class Project_widget : public QWidget
{
  Q_OBJECT
  public:
    Project_widget(Task_queue & task_queue);
  private:
    Project m_project;
    Task_queue & m_task_queue;
  signals:
    void instruments_updated
    (
        std::vector<std::shared_ptr<Adjustable_audio_source>> instruments
    );
    void instrument_selected
    (
        std::shared_ptr<Adjustable_audio_source> instrument
    );
    void tunings_updated(std::vector<std::shared_ptr<Tuning>> tunings);
    void tuning_updated();
    void tuning_selected(std::shared_ptr<Tuning> tuning);
  public slots:
    void add_instrument(std::shared_ptr<Adjustable_audio_source> instrument);
    void add_tuning(std::shared_ptr<Tuning> tuning);
};
