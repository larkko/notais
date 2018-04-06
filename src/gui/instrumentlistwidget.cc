#include "instrumentlistwidget.hh"

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QScrollArea>

#include "editinstrumentwidget.hh"

#include "../lib/audio/oscillator.hh"

Instrument_list_item_widget::Instrument_list_item_widget
(
    std::shared_ptr<Adjustable_audio_source> instrument,
    Task_queue & task_queue
)
    : m_instrument(instrument)
{
    Edit_instrument_widget * edit_window = new Edit_instrument_widget
    (
        m_instrument,
        task_queue,
        this,
        Qt::Window
    );

    QHBoxLayout * layout = new QHBoxLayout();

    QLabel * info_label = new QLabel("instrument");
    layout->addWidget(info_label);
    QPushButton * select_button = new QPushButton("select");
    layout->addWidget(select_button);
    QPushButton * edit_button = new QPushButton("edit");
    layout->addWidget(edit_button);

    this->setLayout(layout);

    QObject::connect
    (
        select_button,
        &QPushButton::pressed,
        this,
        [&]()
        {
            emit selected(m_instrument);
        }
    );

    QObject::connect
    (
        edit_button,
        &QPushButton::pressed,
        this,
        [&, edit_window]()
        {
            edit_window->show();
        }
    );

    QObject::connect
    (
        this,
        &Instrument_list_item_widget::instruments_updated,
        edit_window,
        &Edit_instrument_widget::instruments_updated
    );

    QObject::connect
    (
        this,
        &Instrument_list_item_widget::tunings_updated,
        edit_window,
        &Edit_instrument_widget::tunings_updated
    );
    
    QObject::connect
    (
        edit_window,
        &Edit_instrument_widget::instrument_updated,
        this,
        &Instrument_list_item_widget::instrument_updated
    );
}

std::shared_ptr<Adjustable_audio_source const>
Instrument_list_item_widget::instrument() const
{
    return m_instrument;
}

Instrument_list_widget::Instrument_list_widget(Task_queue & task_queue)
    : m_task_queue(task_queue)
{
    QVBoxLayout * layout = new QVBoxLayout();

    m_instrument_list = new QWidget();
    m_instrument_list->setLayout(new QVBoxLayout());
    m_instrument_list->layout()->setAlignment(Qt::AlignTop);
    
    QScrollArea * instrument_list_area = new QScrollArea();
    instrument_list_area->setWidgetResizable(true);
    instrument_list_area->setWidget(m_instrument_list);

    layout->addWidget(instrument_list_area);

    QHBoxLayout * add_button_layout = new QHBoxLayout();
    QPushButton * add_oscillator = new QPushButton("Add oscillator");
    add_button_layout->addWidget(add_oscillator);
    QPushButton * add_sequence = new QPushButton("Add sequence");
    add_button_layout->addWidget(add_sequence);
    layout->addLayout(add_button_layout);

    this->setLayout(layout);

    QObject::connect
    (
        this,
        &Instrument_list_widget::instruments_updated,
        this,
        &Instrument_list_widget::update_list
    );

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

    QObject::connect
    (
        add_sequence,
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
                        std::make_shared<Sequence>
                        (
                            Sequence()
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
    std::vector<std::shared_ptr<Adjustable_audio_source const>> found;
    
    for(auto widget : m_instrument_list->findChildren<Instrument_list_item_widget *>
                        (QString(), Qt::FindDirectChildrenOnly))
    {
        if(std::find
           (
                instruments.begin(),
                instruments.end(),
                widget->instrument()
            ) == instruments.end())
        {
            delete widget;
        }
        else
        {
            found.push_back(widget->instrument());
            widget->update();
        }
    }
    for(auto & instrument : instruments)
    {
        if(std::find(found.begin(), found.end(), instrument) == found.end())
        {
            Instrument_list_item_widget * item =
                new Instrument_list_item_widget(instrument, m_task_queue);
            m_instrument_list->layout()->addWidget(item);
    
            QObject::connect
            (
                item,
                &Instrument_list_item_widget::selected,
                this,
                &Instrument_list_widget::selected
            );
    
            QObject::connect
            (
                this,
                &Instrument_list_widget::instruments_updated,
                item,
                &Instrument_list_item_widget::instruments_updated
            );
    
            QObject::connect
            (
                this,
                &Instrument_list_widget::tunings_updated,
                item,
                &Instrument_list_item_widget::tunings_updated
            );
            
            
            QObject::connect
            (
                item,
                &Instrument_list_item_widget::instrument_updated,
                this,
                &Instrument_list_widget::instrument_updated
            );
    
            emit item->instruments_updated(instruments);
        }
    }
}
