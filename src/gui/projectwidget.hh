#pragma once

#include <QWidget>
#include <memory>

#include "../lib/audio/adjustableaudiosource.hh"
#include "../lib/project/project.hh"

class Project_widget : public QWidget
{
  Q_OBJECT
  public:
    Project_widget();
  private:
    Project m_project;
  signals:
    void instruments_updated
    (
        std::vector<std::shared_ptr<Adjustable_audio_source>> instruments
    );
    void instrument_selected
    (
        std::shared_ptr<Adjustable_audio_source> instrument
    );
  public slots:
    void add_instrument(std::shared_ptr<Adjustable_audio_source> instrument);
};