#pragma once

#include <QWidget>
#include <memory>

#include "../lib/audio/adjustableaudiosource.hh"

class Project_widget : public QWidget
{
  Q_OBJECT
  public:
    Project_widget();
  public slots:
    void add_instrument(std::shared_ptr<Adjustable_audio_source> instrument);
};