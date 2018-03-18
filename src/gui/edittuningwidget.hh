#pragma once

#include <QWidget>

#include <memory>

#include "../lib/tuning/tuning.hh"
#include "../lib/tuning/equaltemperament.hh"
#include "taskqueue.hh"

class Edit_tuning_widget : public QWidget
{
  Q_OBJECT
  public:
    Edit_tuning_widget
    (
        std::shared_ptr<Tuning> tuning,
        Task_queue & task_queue,
        QWidget * parent = nullptr,
        Qt::WindowFlags flags = Qt::WindowFlags()
    );
  private:
  signals:
    void updated();
};

class Edit_equal_temperament_widget : public QWidget
{
  Q_OBJECT
  public:
    Edit_equal_temperament_widget
    (
        std::shared_ptr<Equal_temperament> tuning,
        Task_queue & task_queue,
        QWidget * parent = nullptr
    );
  private:
    std::shared_ptr<Equal_temperament> m_tuning;
    Task_queue & m_task_queue;
  signals:
    void updated();
};
