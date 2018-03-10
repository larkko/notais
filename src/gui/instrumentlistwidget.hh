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
    std::unique_ptr<QWidget> m_edit_window;
  signals:
    void selected(std::shared_ptr<Adjustable_audio_source> instrument);
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
    void selected(std::shared_ptr<Adjustable_audio_source> instrument);
  public slots:
    void update_list
    (
        std::vector<std::shared_ptr<Adjustable_audio_source>> instruments
    );
};
