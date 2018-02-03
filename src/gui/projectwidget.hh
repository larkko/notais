#pragma once

#include <QWidget>
#include <QVBoxLayout>

class Project_widget : public QWidget
{
  Q_OBJECT
  public:
    Project_widget();
  private:
    QVBoxLayout * m_instrument_list_layout;
    QVBoxLayout * m_tuning_list_layout;
};