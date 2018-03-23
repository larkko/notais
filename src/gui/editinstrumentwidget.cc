#include "editinstrumentwidget.hh"

#include <typeindex>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTabWidget>
#include <QDial>
#include <QComboBox>

#include "../lib/util/util.hh"
#include "effectlistwidget.hh"

Edit_instrument_widget::Edit_instrument_widget
(
    std::shared_ptr<Adjustable_audio_source> instrument,
    Task_queue & task_queue,
    QWidget * parent
)
    : QWidget(parent)
{
    QVBoxLayout * layout = new QVBoxLayout();

    QTabWidget * tabs = new QTabWidget();
    layout->addWidget(tabs);

    QWidget * general_tab = new Edit_instrument_general_tab_widget
    (
        instrument,
        task_queue
    );
    tabs->addTab(general_tab, "general");

    QWidget * instrument_tab = nullptr;
    std::shared_ptr<Audio_source> audio_source = instrument->audio_source();
    std::type_index type = util::underlying_type(audio_source);
    if(type == std::type_index(typeid(Oscillator)))
    {
        std::shared_ptr<Oscillator> oscillator =
            std::static_pointer_cast<Oscillator>(audio_source);
        instrument_tab = new Edit_oscillator_widget(oscillator, task_queue);
    }
    else
    {
        instrument_tab = new QLabel("editing not supported for this instrument");
    }
    tabs->addTab(instrument_tab, "instrument");

    Effect_list_widget * effects_tab = new Effect_list_widget(task_queue);
    tabs->addTab(effects_tab, "effects");

    this->setLayout(layout);

    QObject::connect
    (
        effects_tab,
        &Effect_list_widget::add_effect,
        this,
        [&, instrument](std::shared_ptr<Effect> effect)
        {
            atomic_perform
            (
                task_queue,
                [=]()
                {
                    instrument->effect_stack().add_effect(effect);
                }
            );
            emit effects_updated(instrument->effect_stack().effects());
        }
    );

    QObject::connect
    (
        this,
        &Edit_instrument_widget::effects_updated,
        effects_tab,
        &Effect_list_widget::update_list
    );
}

Edit_instrument_general_tab_widget::Edit_instrument_general_tab_widget
(
    std::shared_ptr<Adjustable_audio_source> instrument,
    Task_queue & task_queue,
    QWidget * parent
)
    : QWidget(parent),
      m_instrument(instrument)
{
    QVBoxLayout * layout = new QVBoxLayout();

    QHBoxLayout * volume_layout = new QHBoxLayout();
    layout->addLayout(volume_layout);
    QLabel * volume_label = new QLabel("volume: ");
    volume_layout->addWidget(volume_label);
    QDial * volume_dial = new QDial();
    volume_layout->addWidget(volume_dial);
    volume_dial->setMinimum(0);
    volume_dial->setMaximum(100);
    volume_dial->setValue(volume_dial->maximum() * m_instrument->volume());

    QObject::connect
    (
        volume_dial,
        &QDial::sliderMoved,
        this,
        [=, &task_queue](int position)
        {
            atomic_perform
            (
                task_queue,
                [=]()
                {
                    m_instrument->set_volume
                    (
                        float(position)/float(volume_dial->maximum())
                    );
                }
            );
        }
    );

    this->setLayout(layout);
}

Edit_oscillator_widget::Edit_oscillator_widget
(
    std::shared_ptr<Oscillator> oscillator,
    Task_queue & task_queue,
    QWidget * parent
)
    : QWidget(parent),
      m_oscillator(oscillator)
{
    QVBoxLayout * layout = new QVBoxLayout();

    QHBoxLayout * type_layout = new QHBoxLayout();
    QLabel * type_label = new QLabel("type: ");
    type_layout->addWidget(type_label);
    QComboBox * type_selector = new QComboBox();
    type_selector->addItems({"Sine", "Square", "Saw", "White noise"});
    type_layout->addWidget(type_selector);
    layout->addLayout(type_layout);

    QObject::connect
    (
        type_selector,
        &QComboBox::currentTextChanged,
        this,
        [=, &task_queue](QString const & text)
        {
            atomic_perform
            (
                task_queue,
                [=]()
                {
                    if(text == "Sine")
                        m_oscillator->set_type(Oscillator::Type::Sine);
                    else if(text == "Square")
                        m_oscillator->set_type(Oscillator::Type::Square);
                    else if(text == "Saw")
                        m_oscillator->set_type(Oscillator::Type::Saw);
                    else if(text == "White noise")
                        m_oscillator->set_type(Oscillator::Type::White_noise);
                }
            );
        }
    );

    this->setLayout(layout);
}





