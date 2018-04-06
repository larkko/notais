#include "tuninglistwidget.hh"

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QScrollArea>

#include "../lib/tuning/equaltemperament.hh"
#include "edittuningwidget.hh"

Tuning_list_item_widget::Tuning_list_item_widget
(
    std::shared_ptr<Tuning> tuning,
    Task_queue & task_queue
)
    : m_tuning(tuning)
{
    Edit_tuning_widget * edit_window = new Edit_tuning_widget
    (
        m_tuning,
        task_queue,
        this,
        Qt::Window
    );

    QHBoxLayout * layout = new QHBoxLayout();

    QLabel * info_label = new QLabel("tuning");
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
            emit selected(m_tuning);
        }
    );

    QObject::connect
    (
        edit_button,
        &QPushButton::pressed,
        this,
        [=]()
        {
            edit_window->show();
        }
    );

    QObject::connect
    (
        edit_window,
        &Edit_tuning_widget::updated,
        this,
        &Tuning_list_item_widget::tuning_updated
    );
}

std::shared_ptr<Tuning const> Tuning_list_item_widget::tuning() const
{
    return m_tuning;
}

Tuning_list_widget::Tuning_list_widget(Task_queue & task_queue)
    : m_task_queue(task_queue)
{
    QVBoxLayout * layout = new QVBoxLayout();

    m_tuning_list = new QWidget();
    m_tuning_list->setLayout(new QVBoxLayout());
    m_tuning_list->layout()->setAlignment(Qt::AlignTop);
    
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
                    /*Default equal temperament set to 12EDO*/
                    Equal_temperament(12.0, 2.0, 440.0)
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
    std::vector<std::shared_ptr<Tuning const>> found;
    for(auto widget : m_tuning_list->findChildren<Tuning_list_item_widget *>
                        (QString(), Qt::FindDirectChildrenOnly))
    {
        if(std::find(tunings.begin(), tunings.end(), widget->tuning())
           == tunings.end())
        {
            delete widget;
        }
        else
        {
            found.push_back(widget->tuning());
            widget->update();
        }
    }

    for(auto & tuning : tunings)
    {
        if(std::find(found.begin(), found.end(), tuning) == found.end())
        {
            Tuning_list_item_widget * item =
                new Tuning_list_item_widget(tuning, m_task_queue);
            m_tuning_list->layout()->addWidget(item);
    
            QObject::connect
            (
                item,
                &Tuning_list_item_widget::selected,
                this,
                &Tuning_list_widget::selected
            );
    
            QObject::connect
            (
                item,
                &Tuning_list_item_widget::tuning_updated,
                this,
                &Tuning_list_widget::tuning_updated
            );
        }
    }
}



