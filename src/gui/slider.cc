#include "slider.hh"

#include <QVBoxLayout>

Slider::Slider()
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

void Slider::set_upper_limit(float limit)
{
    m_slider->setMaximum(maximum_position * limit);
}

void Slider::set_position(float position)
{
    m_slider->setValue(maximum_position * position);
}

float Slider::position() const
{
    return float(m_slider->value()) / float(maximum_position);
}
