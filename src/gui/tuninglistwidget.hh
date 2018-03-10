#pragma once

#include <memory>

#include <QWidget>

#include "../lib/tuning/tuning.hh"
#include "taskqueue.hh"

class Tuning_list_item_widget : public QWidget
{
  Q_OBJECT
  public:
    Tuning_list_item_widget
    (
        std::shared_ptr<Tuning> tuning,
        Task_queue & task_queue
    );
  private:
    std::shared_ptr<Tuning> m_tuning;
    std::unique_ptr<QWidget> m_edit_window;
  signals:
    void selected(std::shared_ptr<Tuning> tuning);
};

class Tuning_list_widget : public QWidget
{
  Q_OBJECT
  public:
    Tuning_list_widget(Task_queue & task_queue);
  private:
    QWidget * m_tuning_list;
    Task_queue & m_task_queue;
  signals:
    void add_tuning(std::shared_ptr<Tuning> tuning);
    void selected(std::shared_ptr<Tuning> tuning);
  public slots:
    void update_list(std::vector<std::shared_ptr<Tuning>> tunings);
};
