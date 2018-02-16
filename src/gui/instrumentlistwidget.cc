#include "instrumentlistwidget.hh"

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

Instrument_list_item_widget::Instrument_list_item_widget
(
    std::shared_ptr<Adjustable_audio_source> const & instrument
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

    layout->addWidget(m_instrument_list);

    this->setLayout(layout);
    update_list({});
}

void Instrument_list_widget::update_list
(
    std::vector<std::shared_ptr<Adjustable_audio_source>> const & instruments
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