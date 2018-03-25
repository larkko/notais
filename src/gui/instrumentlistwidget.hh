#pragma once

#include <QWidget>

#include "../lib/audio/adjustableaudiosource.hh"
#include "taskqueue.hh"

class Instrument_list_item_widget : public QWidget
{
  Q_OBJECT
  public:
    Instrument_list_item_widget
    (
        std::shared_ptr<Adjustable_audio_source> instrument,
        Task_queue & task_queue
    );
  private:
    std::shared_ptr<Adjustable_audio_source> m_instrument;
  signals:
    void selected(std::shared_ptr<Adjustable_audio_source> instrument);
    /*Some instruments can reference others. This allows passing the
      updated list of instruments to all relevant instrument editing widgets.*/
    void instruments_updated
    (
        std::vector<std::shared_ptr<Adjustable_audio_source>> instruments
    );
};

class Instrument_list_widget : public QWidget
{
  Q_OBJECT
  public:
    Instrument_list_widget(Task_queue & task_queue);
  private:
    QWidget * m_instrument_list;
    Task_queue & m_task_queue;
  signals:
    void add_instrument
    (
        std::shared_ptr<Adjustable_audio_source> instrument
    );
    void instruments_updated
    (
        std::vector<std::shared_ptr<Adjustable_audio_source>> instruments
    );
    void selected(std::shared_ptr<Adjustable_audio_source> instrument);
  private slots:
    void update_list
    (
        std::vector<std::shared_ptr<Adjustable_audio_source>> instruments
    );
};
