#pragma once

#include <memory>

#include <QWidget>

#include "../lib/effects/effect.hh"
#include "../lib/effects/envelope.hh"
#include "taskqueue.hh"

class Edit_effect_widget : public QWidget
{
  Q_OBJECT
  public:
    Edit_effect_widget
    (
        std::shared_ptr<Effect> effect,
        Task_queue & task_queue
    );
  private:
};

class Edit_envelope_widget : public QWidget
{
  Q_OBJECT
  public:
    Edit_envelope_widget
    (
        std::shared_ptr<Envelope> envelope,
        Task_queue & task_queue
    );
  private:
};
