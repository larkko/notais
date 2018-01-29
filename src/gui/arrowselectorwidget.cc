#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

#include "arrowselectorwidget.hh"

Arrow_selector_widget::Arrow_selector_widget
(
    std::function<std::string (size_t)> get_description,
    std::function<size_t ()> get_index,
    std::function<size_t ()> get_count,
    std::function<void (size_t)> set_index
)
{
    QHBoxLayout * layout = new QHBoxLayout;
    QLabel * help_text = new QLabel("Audio device: ");
    QPushButton * previous_button = new QPushButton("<");
    QLabel * description_label = new QLabel;
    QPushButton * next_button = new QPushButton(">");

    auto update_description = [=]()
    {
        size_t index = get_index();
        description_label->setText(QString::fromStdString(get_description(index)));
    };

    auto previous = [=]()
    {
        size_t index = get_index();
        if(index > 0)
        {
            set_index(index - 1);
        }
        update_description();
    };

    auto next = [=]()
    {
        size_t index = get_index();
        size_t count = get_count();
        if((count > 0) && (index < (get_count() - 1)))
        {
            set_index(index + 1);
        }
        update_description();
    };

    update_description();

    QSizePolicy size(QSizePolicy::Fixed, QSizePolicy::Fixed);

    help_text->setSizePolicy(size);
    previous_button->setSizePolicy(size);
    description_label->setSizePolicy(size);
    next_button->setSizePolicy(size);

    layout->addWidget(help_text);
    layout->addWidget(previous_button);
    layout->addWidget(description_label);
    layout->addWidget(next_button);

    this->setLayout(layout);

    this->setFixedHeight(layout->minimumSize().height());

    QObject::connect
    (
        previous_button,
        &QPushButton::clicked,
        this,
        previous
    );

    QObject::connect
    (
        next_button,
        &QPushButton::clicked,
        this,
        next
    );
}




