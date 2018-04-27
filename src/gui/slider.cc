#include "slider.hh"

#include <QVBoxLayout>

Slider::Range::Range(float bottom, float top)
    : m_bottom(bottom),
      m_top(top)
{
}

float Slider::Range::bottom() const
{
    return m_bottom;
}

float Slider::Range::top() const
{
    return m_top;
}

float Slider::Range::to_position(float value) const
{
    return (value - m_bottom) / (m_top - m_bottom);
}

float Slider::Range::to_value(float position) const
{
    return (position * (m_top - m_bottom)) + m_bottom;
}


Slider::Slider(Range range)
    : m_range(range)
{
    QVBoxLayout * layout = new QVBoxLayout();
    
    m_slider = new QSlider(Qt::Horizontal);
    m_slider->setMinimum(0);
    m_slider->setMaximum(maximum_position);
    m_slider->setValue(0);
    layout->addWidget(m_slider);
    
    this->setLayout(layout);
    
    QObject::connect
    (
        m_slider,
        &QSlider::valueChanged,
        this,
        &Slider::moved
    );
}

void Slider::set_value(float value)
{
    set_position(m_range.to_position(value));
}

float Slider::value() const
{
    return m_range.to_value(position());
}

void Slider::set_position(float position)
{
    m_slider->setValue(maximum_position * position);
}

float Slider::position() const
{
    return float(m_slider->value()) / float(maximum_position);
}
