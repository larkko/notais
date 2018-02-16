#pragma once

#include <QWidget>
#include <QVBoxLayout>

class Tuning_list_widget : public QWidget
{
  Q_OBJECT
  public:
    Tuning_list_widget();
  private:
    QVBoxLayout * m_tuning_list;
};