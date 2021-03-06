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
    std::shared_ptr<Tuning const> tuning() const;
  private:
    std::shared_ptr<Tuning> m_tuning;
  signals:
    void selected(std::shared_ptr<Tuning> tuning);
    void tuning_updated();
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
    void tuning_updated();
  public slots:
    void update_list(std::vector<std::shared_ptr<Tuning>> tunings);
};
