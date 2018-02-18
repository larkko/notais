#include "tuninglistwidget.hh"

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QScrollArea>

#include "../lib/tuning/equaltemperament.hh"

Tuning_list_item_widget::Tuning_list_item_widget
(
    std::shared_ptr<Tuning> tuning
)
    : m_tuning(tuning)
{
    QHBoxLayout * layout = new QHBoxLayout();

    QLabel * info_label = new QLabel("tuning");
    layout->addWidget(info_label);
    QPushButton * select_button = new QPushButton("select");
    layout->addWidget(select_button);

    this->setLayout(layout);

    QObject::connect
    (
        select_button,
        &QPushButton::pressed,
        this,
        [&]()
        {
            emit selected(m_tuning);
        }
    );
}

Tuning_list_widget::Tuning_list_widget()
{
    QVBoxLayout * layout = new QVBoxLayout();

    m_tuning_list = new QWidget();
    m_tuning_list->setLayout(new QVBoxLayout());
    
    QScrollArea * tuning_list_area = new QScrollArea();
    tuning_list_area->setWidgetResizable(true);
    tuning_list_area->setWidget(m_tuning_list);

    layout->addWidget(tuning_list_area);

    QHBoxLayout * add_button_layout = new QHBoxLayout();
    QPushButton * add_equal_temperament
        = new QPushButton("Add equal temperament");
    add_button_layout->addWidget(add_equal_temperament);
    layout->addLayout(add_button_layout);

    this->setLayout(layout);

    QObject::connect
    (
        add_equal_temperament,
        &QPushButton::pressed,
        this,
        [&]()
        {
            emit add_tuning
            (
                std::make_shared<Equal_temperament>
                (
                    /*Use 5EDO as placeholder for now*/
                    Equal_temperament(5.0, 2.0, 440.0)
                )
            );
        }
    );

    update_list({});
}

void Tuning_list_widget::update_list
(
    std::vector<std::shared_ptr<Tuning>> tunings
)
{
    for(auto widget : m_tuning_list->findChildren<QWidget *>
                        (QString(), Qt::FindDirectChildrenOnly))
    {
        delete widget;
    }
    for(auto & tuning : tunings)
    {
        Tuning_list_item_widget * item =
            new Tuning_list_item_widget(tuning);
        m_tuning_list->layout()->addWidget(item);

        QObject::connect
        (
            item,
            &Tuning_list_item_widget::selected,
            this,
            &Tuning_list_widget::selected
        );
    }
}



