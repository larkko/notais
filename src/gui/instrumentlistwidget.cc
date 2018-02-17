#include "instrumentlistwidget.hh"

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QScrollArea>

#include "../lib/audio/oscillator.hh"

Instrument_list_item_widget::Instrument_list_item_widget
(
    std::shared_ptr<Adjustable_audio_source> instrument
)
    : m_instrument(instrument)
{
    QHBoxLayout * layout = new QHBoxLayout();

    QLabel * info_label = new QLabel("instrument");
    layout->addWidget(info_label);
    QPushButton * select_button = new QPushButton("select");
    layout->addWidget(select_button);

    this->setLayout(layout);
}

Instrument_list_widget::Instrument_list_widget()
{
    QVBoxLayout * layout = new QVBoxLayout();

    m_instrument_list = new QWidget();
    m_instrument_list->setLayout(new QVBoxLayout());
    
    QScrollArea * instrument_list_area = new QScrollArea();
    instrument_list_area->setWidgetResizable(true);
    instrument_list_area->setWidget(m_instrument_list);

    layout->addWidget(instrument_list_area);

    QHBoxLayout * add_button_layout = new QHBoxLayout();
    QPushButton * add_oscillator = new QPushButton("Add oscillator");
    add_button_layout->addWidget(add_oscillator);
    layout->addLayout(add_button_layout);

    this->setLayout(layout);

    QObject::connect
    (
        add_oscillator,
        &QPushButton::pressed,
        this,
        [&]()
        {
            emit add_instrument
            (
                std::make_shared<Adjustable_audio_source>
                (
                    Adjustable_audio_source
                    (
                        std::make_shared<Oscillator>
                        (
                            Oscillator(Oscillator::Type::Sine)
                        )
                    )
                )
            );
        }
    );

    update_list({});
}

void Instrument_list_widget::update_list
(
    std::vector<std::shared_ptr<Adjustable_audio_source>> instruments
)
{
    for(auto widget : m_instrument_list->findChildren<QWidget *>
                        (QString(), Qt::FindDirectChildrenOnly))
    {
        delete widget;
    }
    for(auto & instrument : instruments)
    {
        Instrument_list_item_widget * item =
            new Instrument_list_item_widget(instrument);
        m_instrument_list->layout()->addWidget(item);
    }
}