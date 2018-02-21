#include "edittuningwidget.hh"

#include <string>

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>

#include "../lib/util/util.hh"
#include "headingwidget.hh"

Edit_tuning_widget::Edit_tuning_widget
(
    std::shared_ptr<Tuning> tuning,
    QWidget *parent
)
    : QWidget(parent)
{
    std::type_index type = util::underlying_type(tuning);
    if(type == std::type_index(typeid(Equal_temperament)))
    {
        new Edit_equal_temperament_widget
        (
            std::static_pointer_cast<Equal_temperament>(tuning),
            this
        );
    }
    else
    {
        new QLabel("unrecognized tuning", this);
    }
}

Edit_equal_temperament_widget::Edit_equal_temperament_widget
(
    std::shared_ptr<Equal_temperament> tuning,
    QWidget *parent
)
    : QWidget(parent),
      m_tuning(tuning)
{
    QVBoxLayout * layout = new QVBoxLayout();

    Heading_widget * heading = new Heading_widget("Equal temperament", this);
    layout->addWidget(heading);

    QHBoxLayout * steps_layout = new QHBoxLayout();
    QLabel * steps_label = new QLabel("steps: ");
    steps_layout->addWidget(steps_label);
    QLineEdit * steps_input = new QLineEdit(QString(""));
    steps_layout->addWidget(steps_input);
    layout->addLayout(steps_layout);

    QHBoxLayout * interval_layout = new QHBoxLayout();
    QLabel * interval_label = new QLabel("interval ('tave): ");
    interval_layout->addWidget(interval_label);
    QLineEdit * interval_input = new QLineEdit(QString());
    interval_layout->addWidget(interval_input);
    layout->addLayout(interval_layout);

    QHBoxLayout * base_frequency_layout = new QHBoxLayout();
    QLabel * base_frequency_label = new QLabel("base frequency: ");
    base_frequency_layout->addWidget(base_frequency_label);
    QLineEdit * base_frequency_input = new QLineEdit(QString(""));
    base_frequency_layout->addWidget(base_frequency_input);
    layout->addLayout(base_frequency_layout);

    QPushButton * update_button = new QPushButton("update");
    layout->addWidget(update_button);

    auto update_inputs = [=]()
    {
        steps_input->setText
        (
            QString::fromStdString(std::to_string(m_tuning->steps_per_interval()))
        );
        interval_input->setText
        (
            QString::fromStdString(std::to_string(m_tuning->interval_size()))
        );
        base_frequency_input->setText
        (
            QString::fromStdString(std::to_string(m_tuning->base_frequency()))
        );
    };

    update_inputs();

    QObject::connect
    (
        update_button,
        &QPushButton::pressed,
        this,
        [](){}
    );

    this->setLayout(layout);
}






