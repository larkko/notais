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

class Edit_equal_temperament_widget : public QWidget
{
  Q_OBJECT
  public:
    Edit_equal_temperament_widget
    (
        std::shared_ptr<Equal_temperament> tuning,
        QWidget * parent = nullptr
    );
  private:
    std::shared_ptr<Equal_temperament> m_tuning;
};
