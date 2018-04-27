#pragma once

#include <QSlider>

class Slider : public QSlider
{
  Q_OBJECT
  public:
    Slider();
    void set_upper_limit(float limit);
    void set_position(float position);
    float position() const;
  private:
    float m_upper_limit;
    static int constexpr maximum_position = 100;
  signals:
    void moved();
};
