#include <iostream>
#include <math.h>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QTimer>
#include <QLabel>

#include "mainwindow.hh"
#include "arrowselectorwidget.hh"
#include "projectwidget.hh"
#include "../lib/audio/oscillator.hh"
#include "../lib/tuning/equaltemperament.hh"

Main_window::Main_window()
    : m_midi_input(MIDI_input
    (
        [&](MIDI_input::Event e)
        {
            if(e.down)
            {
                m_keyboard.press({e.key, Keyboard::Key::Type::Raw}, e.velocity);
            }
            else
            {
                m_keyboard.release({e.key, Keyboard::Key::Type::Raw});
            }
            emit keyboard_state_changed();
        }
    )),
    /*Offset of the middle A key in MIDI key numberings. The middle A
      is commonly used when considering tuning. Furthermore, it's in the middle
      of the keyboard (max MIDI note value = 127), making it a convenient
      center point.*/
    m_keyboard(69),
    m_audio_out(Audio_output
    (
        44100, //sample rate
        256, //buffer frame count
        2, //channel count
        [&](Audio_data & destination)
        {
            m_keyboard.for_each
            ([&](Keyboard::Keypress press, Keyboard::Press_identifier press_id)
                {
                    if(m_keyboard.key_is_active
                      ({press.key, Keyboard::Key::Type::Offset}))
                    {
                        m_active_instrument->get_samples
                        (
                            destination,
                            m_active_tuning->frequency_at(press.key), //frequency
                            press.velocity, //volume
                            destination.frame_count(),
                            press.elapsed_time, //source offset
                            0 //destination offset
                        );
                    }
                },
                Keyboard::Key::Type::Offset
            );
            m_keyboard.advance_time(destination.frame_count());
        }
    )),
    m_audio_stop_timer(new QTimer(this)),
    m_active_instrument
    (
        std::make_shared<Adjustable_audio_source>
        (
            std::make_shared<Oscillator>(Oscillator(Oscillator::Type::Sine))
        )
    ),
    m_active_tuning
    (
        /*Normal 12EDO tuning.*/
        std::make_shared<Equal_temperament>(Equal_temperament(12, 2, 440))
    )
{
    QVBoxLayout * root_layout = new QVBoxLayout;

    QHBoxLayout * top_bar_layout = new QHBoxLayout;
    root_layout->addLayout(top_bar_layout);

    QLabel * volume_label = new QLabel("Volume: ");
    top_bar_layout->addWidget(volume_label);

    QSlider * volume_slider = new QSlider(Qt::Horizontal);
    volume_slider->setMinimum(0);
    volume_slider->setMaximum(100);
    volume_slider->setValue(m_audio_out.volume() * volume_slider->maximum());
    top_bar_layout->addWidget(volume_slider);

    Arrow_selector_widget * audio_device_selector
    = new Arrow_selector_widget
    (
        [&](size_t index){return m_audio_out.device_description(index);},
        [&](){return m_audio_out.device_index();},
        [&](){return m_audio_out.device_count();},
        [&](size_t index){m_audio_out.set_device(index);}
    );
    top_bar_layout->addWidget(audio_device_selector);

    Project_widget * project_widget = new Project_widget();
    root_layout->addWidget(project_widget);

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
            float volume = float(volume_slider->value()) /
                           float(volume_slider->maximum());
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

    QObject::connect
    (
        keyboard_widget,
        &Keyboard_widget::key_press_event,
        this,
        [&](int key, float velocity)
        {
            m_keyboard.press({key, Keyboard::Key::Type::Raw}, velocity);
            emit keyboard_state_changed();
        }
    );
    
    QObject::connect
    (
        keyboard_widget,
        &Keyboard_widget::key_release_event,
        this,
        [&](int key)
        {
            m_keyboard.release({key, Keyboard::Key::Type::Raw});
            emit keyboard_state_changed();
        }
    );

    /*Update audio state whenever keyboard state changes*/
    QObject::connect
    (
        this,
        &Main_window::keyboard_state_changed,
        this,
        &Main_window::update_audio_state
    );

    QObject::connect
    (
        project_widget,
        &Project_widget::instrument_selected,
        this,
        [&](std::shared_ptr<Adjustable_audio_source> instrument)
        {
            m_active_instrument = instrument;
        }
    );

    QObject::connect
    (
        project_widget,
        &Project_widget::tuning_selected,
        this,
        [&](std::shared_ptr<Tuning> tuning)
        {
            m_active_tuning = tuning;
        }
    );

    m_audio_stop_timer->setTimerType(Qt::VeryCoarseTimer);
    m_audio_stop_timer->setSingleShot(true);

    QObject::connect
    (
        m_audio_stop_timer,
        &QTimer::timeout,
        this,
        &Main_window::update_audio_state
    );

    QObject::connect
    (
        this,
        &Main_window::keyboard_state_changed,
        this,
        &Main_window::start_audio_stop_timer
    );
}

void Main_window::update_audio_state()
{
    bool keyboard_active = m_keyboard.is_active();

    if(!m_audio_out.is_active() && keyboard_active)
    {
        m_audio_out.start();
    }
    else if(m_audio_out.is_active() && !keyboard_active && !m_audio_stop_timer->isActive())
    {
        m_audio_out.stop();
    }
}

void Main_window::start_audio_stop_timer()
{
    /*milliseconds*/
    auto timer_limit = 5*60*1000;
    m_audio_stop_timer->start(timer_limit);
}












