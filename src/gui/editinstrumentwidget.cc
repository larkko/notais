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
#include "headingwidget.hh"

Edit_instrument_widget::Edit_instrument_widget
(
    std::shared_ptr<Adjustable_audio_source> instrument,
    Task_queue & task_queue,
    QWidget * parent,
    Qt::WindowFlags flags
)
    : QWidget(parent, flags)
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
    else if(type == std::type_index(typeid(Sequence)))
    {
        std::shared_ptr<Sequence> sequence =
            std::static_pointer_cast<Sequence>(audio_source);
        auto edit_widget = new Edit_sequence_widget(sequence, task_queue);
        instrument_tab = edit_widget;

        QObject::connect
        (
            this,
            &Edit_instrument_widget::instruments_updated,
            edit_widget,
            &Edit_sequence_widget::update_instruments
        );

        QObject::connect
        (
            this,
            &Edit_instrument_widget::tunings_updated,
            edit_widget,
            &Edit_sequence_widget::update_tunings
        );
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
    layout->setAlignment(Qt::AlignTop);

    Heading_widget * heading = new Heading_widget("Oscillator");
    layout->addWidget(heading);

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

Edit_sequence_widget::Edit_sequence_widget
(
    std::shared_ptr<Sequence> sequence,
    Task_queue & task_queue,
    QWidget * parent
)   : QWidget(parent),
      m_sequence(sequence),
      m_task_queue(task_queue)
{
    QVBoxLayout * layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);

    Heading_widget * heading = new Heading_widget("Sequence");
    layout->addWidget(heading);

    QHBoxLayout * top_bar_layout = new QHBoxLayout();
    top_bar_layout->setAlignment(Qt::AlignLeft);
    layout->addLayout(top_bar_layout);

    QLabel * instrument_label = new QLabel("Instrument:");
    top_bar_layout->addWidget(instrument_label);
    m_instrument_selector = new QComboBox();
    top_bar_layout->addWidget(m_instrument_selector);

    QLabel * tuning_label = new QLabel("Tuning:");
    top_bar_layout->addWidget(tuning_label);
    m_tuning_selector = new QComboBox();
    top_bar_layout->addWidget(m_tuning_selector);

    auto editor = new Edit_sequence_pattern_widget(sequence, task_queue);
    layout->addWidget(editor);

    this->setLayout(layout);
}

void Edit_sequence_widget::update_instruments
(
    std::vector<std::shared_ptr<Adjustable_audio_source>> instruments
)
{
    disconnect(m_instrument_selector);
    m_instrument_selector->disconnect(this);
    m_instrument_selector->clear();
    for(auto & instrument : instruments)
    {
        m_instrument_selector->addItem
        (
            "Instrument: " + QString::fromStdString(instrument->name())
        );
    }
    QObject::connect
    (
        m_instrument_selector,
        static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
        this,
        [=](int index)
        {
            if(index < 0) return;
            atomic_perform
            (
                m_task_queue,
                [=]()
                {
                    m_sequence->set_instrument(instruments[index]);
                }
            );
        }
    );
}

void Edit_sequence_widget::update_tunings
(
    std::vector<std::shared_ptr<Tuning>> tunings
)
{
    disconnect(m_tuning_selector);
    m_tuning_selector->disconnect(this);
    m_tuning_selector->clear();
    for(auto & tuning : tunings)
    {
        m_tuning_selector->addItem("Tuning: ");
    }
    QObject::connect
    (
        m_tuning_selector,
        static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
        this,
        [=](int index)
        {
            if(index < 0) return;
            atomic_perform
            (
                m_task_queue,
                [=]()
                {
                    m_sequence->set_tuning(tunings[index]);
                }
            );
        }
    );
}

Edit_sequence_pattern_widget::Edit_sequence_pattern_widget
(
    std::shared_ptr<Sequence> sequence,
    Task_queue & task_queue,
    QWidget * parent
) : QWidget(parent),
    m_sequence(sequence),
    m_task_queue(task_queue)
{
    QVBoxLayout * layout = new QVBoxLayout();
    layout->addWidget(new QLabel("pattern"));
    this->setLayout(layout);
}


