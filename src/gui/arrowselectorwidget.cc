#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

#include "arrowselectorwidget.hh"

Arrow_selector_widget::Arrow_selector_widget
(
    std::function<std::string ()> get_description,
    std::function<size_t ()> get_index,
    std::function<size_t ()> get_count,
    std::function<void (size_t)> set_index
)
    : m_get_description(get_description),
      m_get_index(get_index),
      m_get_count(get_count),
      m_set_index(set_index)
{
    QHBoxLayout * layout = new QHBoxLayout;
    QLabel * help_text = new QLabel("Audio device: ");
    QPushButton * previous_button = new QPushButton("<");
    QLabel * description_label = new QLabel("text here");
    QPushButton * next_button = new QPushButton(">");

    layout->addWidget(help_text);
    layout->addWidget(previous_button);
    layout->addWidget(description_label);
    layout->addWidget(next_button);    

    this->setLayout(layout);
}