#pragma once

#include <QWidget>

#include "../lib/audio/adjustableaudiosource.hh"

class Instrument_list_item_widget : public QWidget
{
  Q_OBJECT
  public:
    Instrument_list_item_widget
    (
        std::shared_ptr<Adjustable_audio_source> instrument
    );
  private:
    std::shared_ptr<Adjustable_audio_source> m_instrument;
  signals:
    void selected(std::shared_ptr<Adjustable_audio_source> instrument);
};

class Instrument_list_widget : public QWidget
{
  Q_OBJECT
  public:
    Instrument_list_widget();
  private:
    QWidget * m_instrument_list;
  signals:
    void add_instrument
    (
        std::shared_ptr<Adjustable_audio_source> instrument
    );
  public slots:
    void update_list
    (
        std::vector<std::shared_ptr<Adjustable_audio_source>> instruments
    );
};