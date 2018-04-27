#pragma once

#include <QWidget>
#include <QSlider>

class Slider : public QWidget
{
  Q_OBJECT
  public:
    Slider();
    void set_upper_limit(float limit);
    void set_position(float position);
    float position() const;
  private:
    float m_upper_limit;
    QSlider * m_slider;
    static int constexpr maximum_position = 100;
  signals:
    void moved();
};
