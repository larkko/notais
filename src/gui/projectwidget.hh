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
  public slots:
    void add_instrument(std::shared_ptr<Adjustable_audio_source> instrument);
};