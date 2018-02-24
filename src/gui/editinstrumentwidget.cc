#include "editinstrumentwidget.hh"

#include <typeindex>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTabWidget>
#include <QDial>
#include <QComboBox>

#include "../lib/util/util.hh"

Edit_instrument_widget::Edit_instrument_widget
(
    std::shared_ptr<Adjustable_audio_source> instrument,
    QWidget * parent
)
    : QWidget(parent)
{
    QVBoxLayout * layout = new QVBoxLayout();

    QTabWidget * tabs = new QTabWidget();
    layout->addWidget(tabs);

    QWidget * general_tab = new Edit_instrument_general_tab_widget(instrument);
    tabs->addTab(general_tab, "general");

    QWidget * instrument_tab = nullptr;
    std::shared_ptr<Audio_source> audio_source = instrument->audio_source();
    std::type_index type = util::underlying_type(audio_source);
    if(type == std::type_index(typeid(Oscillator)))
    {
        std::shared_ptr<Oscillator> oscillator =
            std::static_pointer_cast<Oscillator>(audio_source);
        instrument_tab = new Edit_oscillator_widget(oscillator);
    }
    else
    {
        instrument_tab = new QLabel("editing not supported for this instrument");
    }
    tabs->addTab(instrument_tab, "instrument");

    QLabel * effects_tab = new QLabel("effects tab");
    tabs->addTab(effects_tab, "effects");

    this->setLayout(layout);
}

Edit_instrument_general_tab_widget::Edit_instrument_general_tab_widget
(
    std::shared_ptr<Adjustable_audio_source> instrument,
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
        [=](int position)
        {
            m_instrument->set_volume(float(position)/float(volume_dial->maximum()));
        }
    );

    this->setLayout(layout);
}

Edit_oscillator_widget::Edit_oscillator_widget
(
    std::shared_ptr<Oscillator> oscillator,
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
    type_selector->addItems({"Sine", "Square", "Saw"});
    type_layout->addWidget(type_selector);
    layout->addLayout(type_layout);

    QObject::connect
    (
        type_selector,
        &QComboBox::currentTextChanged,
        this,
        [=](QString const & text)
        {
            if(text == "Sine")
                m_oscillator->set_type(Oscillator::Type::Sine);
            else if(text == "Square")
                m_oscillator->set_type(Oscillator::Type::Square);
            else if(text == "Saw")
                m_oscillator->set_type(Oscillator::Type::Saw);
        }
    );

    this->setLayout(layout);
}





