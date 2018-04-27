#include <iostream>
#include <math.h>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QTimer>
#include <QLabel>

#include "mainwindow.hh"
#include "arrowselectorwidget.hh"
#include "slider.hh"
#include "projectwidget.hh"
#include "taskqueue.hh"
#include "../lib/audio/oscillator.hh"
#include "../lib/tuning/equaltemperament.hh"

Main_window::Main_window()
    : m_midi_input
    (
        [&](MIDI::Event e)
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
    ),
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
        [&](Audio_data & destination){ use_instrument(destination); }
    )),
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
    ),
    m_project_tasks([](){})
{
    QVBoxLayout * root_layout = new QVBoxLayout;

    QHBoxLayout * top_bar_layout = new QHBoxLayout;
    root_layout->addLayout(top_bar_layout);

    QLabel * volume_label = new QLabel("Volume: ");
    top_bar_layout->addWidget(volume_label);

    Slider * volume_slider = new Slider();
    volume_slider->set_position(m_audio_out.volume());
    top_bar_layout->addWidget(volume_slider);

    Project_widget * project_widget = new Project_widget(m_project_tasks);
    root_layout->addWidget(project_widget);

    Keyboard_widget * keyboard_widget = new Keyboard_widget(m_keyboard);
    root_layout->addWidget(keyboard_widget);

    this->setLayout(root_layout);

    /*Update audio output volume when volume slider is used*/
    QObject::connect
    (
        volume_slider,
        &Slider::moved,
        this,
        [=]()
        {
            m_audio_out.set_volume(volume_slider->position());
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

    auto register_tuning_update = [&, keyboard_widget]()
    {
        keyboard_widget->change_pattern
        (
            m_active_tuning->steps_in_pattern(),
            m_keyboard.offset()
        );
        keyboard_widget->update();
    };

    QObject::connect
    (
        project_widget,
        &Project_widget::tuning_selected,
        this,
        [&, keyboard_widget, register_tuning_update]
        (std::shared_ptr<Tuning> tuning)
        {
            m_active_tuning = tuning;
            register_tuning_update();
        }
    );

    QObject::connect
    (
        project_widget,
        &Project_widget::tuning_updated,
        this,
        register_tuning_update
    );

    update_audio_state();
    register_tuning_update();
}

void Main_window::update_audio_state()
{
    if(!m_audio_out.is_active())
    {
        m_audio_out.start();
    }
}

void Main_window::use_instrument(Audio_data & audio_output_buffer)
{
    m_keyboard.for_each
    ([&](Keyboard::Keypress press, Keyboard::Press_identifier press_id)
        {
            if(m_keyboard.key_is_active
              ({press.key, Keyboard::Key::Type::Offset}, true))
            {
                auto seconds_released = audio_output_buffer
                                       .sample_rate()
                                       .samples_to_seconds(press.time_since_release());
                if(seconds_released <= m_active_instrument->linger_time())
                {
                    m_active_instrument->get_samples
                    (
                        audio_output_buffer,
                        m_active_tuning->frequency_at(press.key), //frequency
                        press.velocity, //volume
                        audio_output_buffer.frame_count(),
                        press.elapsed_time, //source offset
                        press.release_offset,
                        0 //destination offset
                    );
                }
                else
                {
                    m_keyboard.expire(press_id);
                }
            }
        },
        Keyboard::Key::Type::Offset
    );

    m_keyboard.advance_time(audio_output_buffer.frame_count());

    while(m_project_tasks.pop
    (
        [](std::function<void ()> & function){ function(); }
    )){}
}







