#pragma once

#include <memory>

#include <QWidget>

#include "../lib/audio/adjustableaudiosource.hh"

class Edit_instrument_widget : public QWidget
{
  Q_OBJECT
  public:
    Edit_instrument_widget
    (
        std::shared_ptr<Adjustable_audio_source> instrument,
        QWidget * parent = nullptr
    );
  private:
};

class Edit_instrument_general_tab_widget : public QWidget
{
  Q_OBJECT
  public:
    Edit_instrument_general_tab_widget
    (
        std::shared_ptr<Adjustable_audio_source> instrument,
        QWidget * parent = nullptr
    );
  private:
    std::shared_ptr<Adjustable_audio_source> m_instrument;
};
