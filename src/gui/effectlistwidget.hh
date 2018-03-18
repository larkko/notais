#pragma once

#include <memory>

#include <QWidget>

#include "../lib/effects/effect.hh"
#include "taskqueue.hh"

class Effect_list_widget : public QWidget
{
  Q_OBJECT
  public:
    Effect_list_widget(Task_queue & task_queue);
  private:
    QWidget * m_effect_list;
    Task_queue & m_task_queue;
  signals:
    void add_effect(std::shared_ptr<Effect> effect);
  public slots:
    void update_list(std::vector<std::shared_ptr<Effect>> effects);
};
