#pragma once

#include <QWidget>
#include <QVBoxLayout>

class Instrument_list_widget : public QWidget
{
  Q_OBJECT
  public:
    Instrument_list_widget();
  private:
    QVBoxLayout * m_instrument_list;
};