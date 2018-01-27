#include <iostream>
#include <math.h>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>

#include "mainwindow.hh"
#include "../lib/audio/oscillator.hh"
#include "../lib/tuning/equaltemperament.hh"

Main_window::Main_window()
    : m_midi_input(MIDI_input
    (
        [&](MIDI_input::Event e)
        {
            if(e.down)
            {
                m_keyboard.set(e.key, Keyboard::Keypress(e.velocity));
            }
            else
            {
                m_keyboard.set(e.key, Keyboard::Keypress(0.0f));
            }
            emit keyboard_state_changed();
        }
    )),
    m_audio_out(Audio_output
    (
        [&](Audio_data & destination)
        {
            for(int key = 0; key < static_cast<int>(m_keyboard.key_count()); ++key)
            {
                if(m_keyboard.key_is_active(key))
                {
                    m_active_instrument->get_samples
                    (
                        destination,
                        m_active_tuning->frequency_at(key), //frequency
                        m_keyboard.at(key).velocity, //volume
                        destination.frame_count(),
                        m_keyboard.at(key).elapsed_time, //source offset
                        0 //destination offset
                    );
                }
            }
            destination.clamp_samples();
            m_keyboard.advance_time(destination.frame_count());
        }
    )),
    m_active_instrument
    (
        std::make_unique<Oscillator>(Oscillator(Oscillator::Type::Sine))
    ),
    m_active_tuning
    (
        /*Base frequency is set to the frequency of midi note 0 here.
          Otherwise this is normal 12EDO tuning.*/
        std::make_unique<Equal_temperament>(Equal_temperament(12, 2, 8.175798))
    )
{
    QVBoxLayout * root_layout = new QVBoxLayout;

    QSlider * volume_slider = new QSlider(Qt::Horizontal);
    volume_slider->setMinimum(0);
    volume_slider->setMaximum(100);
    volume_slider->setValue(m_audio_out.volume() * volume_slider->maximum());
    root_layout->addWidget(volume_slider);

    Keyboard_widget * keyboard_widget = new Keyboard_widget(m_keyboard);
    root_layout->addWidget(keyboard_widget);

    this->setLayout(root_layout);

    /*Update audio output volume when volume slider is used*/
    QObject::connect
    (
        volume_slider,
        &QSlider::sliderMoved,
        this,
        [=]()
        {
            float volume = static_cast<float>(volume_slider->value()) /
                           static_cast<float>(volume_slider->maximum());
            m_audio_out.set_volume(volume);
        }
    );

    /*Update keyboard widget when keyboard state changes*/
    QObject::connect
    (
        this,
        &Main_window::keyboard_state_changed,
        keyboard_widget,
        static_cast<void (Keyboard_widget::*)()>(&Keyboard_widget::update)
    );

    /*Acknowledge keyboard state changes when updated from keyboard widget*/
    QObject::connect
    (
        keyboard_widget,
        &Keyboard_widget::keyboard_state_changed,
        this,
        &Main_window::keyboard_state_changed
    );

    /*Update audio state whenever keyboard state changes*/
    QObject::connect
    (
        this,
        &Main_window::keyboard_state_changed,
        this,
        &Main_window::update_audio_state
    );
}

void Main_window::update_audio_state()
{
    if(!m_audio_out.is_active() && m_keyboard.is_active())
    {
        m_audio_out.start();
    }
    else if(m_audio_out.is_active() && !m_keyboard.is_active())
    {
        m_audio_out.stop();
    }
}














