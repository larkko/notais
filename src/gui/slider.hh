#pragma once

#include <QWidget>
#include <QSlider>

class Slider : public QWidget
{
  Q_OBJECT
  public:
  
    class Range
    {
      public:
        Range(float bottom, float top);
        float bottom() const;
        float top() const;
        float to_position(float value) const;
        float to_value(float position) const;
      private:
        float m_bottom;
        float m_top;
    };
    
    Slider(Range range = Range(0, 1));
    void set_value(float value);
    float value() const;
  private:
    void set_position(float position);
    float position() const;
    Range m_range;
    QSlider * m_slider;
    static int constexpr maximum_position = 100;
  signals:
    void moved();
};
