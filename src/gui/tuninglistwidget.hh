#pragma once

#include <memory>

#include <QWidget>

#include "../lib/tuning/tuning.hh"

class Tuning_list_item_widget : public QWidget
{
  Q_OBJECT
  public:
    Tuning_list_item_widget(std::shared_ptr<Tuning> tuning);
  private:
    std::shared_ptr<Tuning> m_tuning;
  signals:
    void selected(std::shared_ptr<Tuning> tuning);
};

class Tuning_list_widget : public QWidget
{
  Q_OBJECT
  public:
    Tuning_list_widget();
  private:
    QWidget * m_tuning_list;
  signals:
    void add_tuning(std::shared_ptr<Tuning> tuning);
    void selected(std::shared_ptr<Tuning> tuning);
  public slots:
    void update_list(std::vector<std::shared_ptr<Tuning>> tunings);
};