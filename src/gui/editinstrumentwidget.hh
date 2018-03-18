#pragma once

#include <memory>
#include <vector>

#include <QWidget>

#include "../lib/audio/adjustableaudiosource.hh"
#include "../lib/audio/oscillator.hh"
#include "../lib/effects/effect.hh"
#include "taskqueue.hh"

class Edit_instrument_widget : public QWidget
{
  Q_OBJECT
  public:
    Edit_instrument_widget
    (
        std::shared_ptr<Adjustable_audio_source> instrument,
        Task_queue & task_queue,
        QWidget * parent = nullptr
    );
  private:
  signals:
    void effects_updated(std::vector<std::shared_ptr<Effect>> effects);
};

class Edit_instrument_general_tab_widget : public QWidget
{
  Q_OBJECT
  public:
    Edit_instrument_general_tab_widget
    (
        std::shared_ptr<Adjustable_audio_source> instrument,
        Task_queue & task_queue,
        QWidget * parent = nullptr
    );
  private:
    std::shared_ptr<Adjustable_audio_source> m_instrument;
};

class Edit_oscillator_widget : public QWidget
{
  Q_OBJECT
  public:
    Edit_oscillator_widget
    (
        std::shared_ptr<Oscillator> oscillator,
        Task_queue & task_queue,
        QWidget * parent = nullptr
    );
  private:
    std::shared_ptr<Oscillator> m_oscillator;
};
