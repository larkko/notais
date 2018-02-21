#pragma once

#include <QWidget>

#include <memory>

#include "../lib/tuning/tuning.hh"
#include "../lib/tuning/equaltemperament.hh"

class Edit_tuning_widget : public QWidget
{
  Q_OBJECT
  public:
    Edit_tuning_widget
    (
        std::shared_ptr<Tuning> tuning,
        QWidget * parent = nullptr
    );
  private:
};
