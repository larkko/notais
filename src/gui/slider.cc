#include "slider.hh"

Slider::Slider()
    : QSlider(Qt::Horizontal)
{
    setMinimum(0);
    setMaximum(maximum_position);
    setValue(0);
    
    QObject::connect
    (
        this,
        &QSlider::valueChanged,
        this,
        &Slider::moved
    );
}

void Slider::set_upper_limit(float limit)
{
    setMaximum(maximum_position / limit);
}

void Slider::set_position(float position)
{
    setValue(maximum_position * position);
}

float Slider::position() const
{
    return float(value()) / float(maximum());
}
