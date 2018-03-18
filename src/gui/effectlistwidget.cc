#include "effectlistwidget.hh"

#include <iostream>
#include <memory>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QPushButton>

#include "../lib/effects/envelope.hh"

Effect_list_widget::Effect_list_widget(Task_queue &task_queue)
    : m_task_queue(task_queue)
{
    QVBoxLayout * layout = new QVBoxLayout();

    m_effect_list = new QWidget();
    m_effect_list->setLayout(new QVBoxLayout);
    m_effect_list->layout()->setAlignment(Qt::AlignTop);

    QScrollArea * effect_list_area = new QScrollArea();
    effect_list_area->setWidgetResizable(true);
    effect_list_area->setWidget(m_effect_list);

    layout->addWidget(effect_list_area);

    QHBoxLayout * add_button_layout = new QHBoxLayout();
    QPushButton * add_envelope = new QPushButton("Add envelope");
    add_button_layout->addWidget(add_envelope);
    layout->addLayout(add_button_layout);

    this->setLayout(layout);

    QObject::connect
    (
        add_envelope,
        &QPushButton::pressed,
        this,
        [&]()
        {
            emit add_effect
            (
                std::make_shared<Envelope>(Envelope(0.1, 0.1))
            );
        }
    );

    update_list({});
}

void Effect_list_widget::update_list
(
    std::vector<std::shared_ptr<Effect>> effects
)
{
}












