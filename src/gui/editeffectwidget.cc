#include "editeffectwidget.hh"

#include <memory>
#include <string>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "../lib/util/util.hh"
#include "../lib/effects/envelope.hh"
#include "taskqueue.hh"
#include "headingwidget.hh"

Edit_effect_widget::Edit_effect_widget
(
    std::shared_ptr<Effect> effect,
    Task_queue & task_queue
)
{
    QVBoxLayout * layout = new QVBoxLayout();

    std::type_index type = util::underlying_type(effect);

    if(type == std::type_index(typeid(Envelope)))
    {
        auto envelope = std::static_pointer_cast<Envelope>(effect);
        auto edit_envelope = new Edit_envelope_widget(envelope, task_queue);
        layout->addWidget(edit_envelope);
    }
    else
    {
        QLabel * label = new QLabel("Unsupported effect");
        layout->addWidget(label);
    }

    this->setLayout(layout);
}

Edit_envelope_widget::Edit_envelope_widget
(
    std::shared_ptr<Envelope> envelope,
    Task_queue & task_queue
)
{
    QVBoxLayout * layout = new QVBoxLayout();

    Heading_widget * heading = new Heading_widget("Envelope");
    layout->addWidget(heading);

    QHBoxLayout * attack_layout = new QHBoxLayout();
    layout->addLayout(attack_layout);
    QLabel * attack_label = new QLabel("Attack (seconds):");
    attack_layout->addWidget(attack_label);
    QLineEdit * attack_input = new QLineEdit();
    attack_layout->addWidget(attack_input);

    QHBoxLayout * release_layout = new QHBoxLayout();
    layout->addLayout(release_layout);
    QLabel * release_label = new QLabel("Release (seconds):");
    release_layout->addWidget(release_label);
    QLineEdit * release_input = new QLineEdit();
    release_layout->addWidget(release_input);

    QPushButton * set_button = new QPushButton("Set values");
    layout->addWidget(set_button);

    auto update_inputs = [=]()
    {
        attack_input->setText
        (
            QString::fromStdString(std::to_string(envelope->attack_length()))
        );
        release_input->setText
        (
            QString::fromStdString(std::to_string(envelope->release_length()))
        );
    };

    update_inputs();

    QObject::connect
    (
        set_button,
        &QPushButton::clicked,
        this,
        [=, &task_queue]()
        {
            atomic_perform
            (
                task_queue,
                [&]()
                {
                    std::string attack_string = attack_input->text().toStdString();
                    std::string release_string = release_input->text().toStdString();
                    try
                    {
                        double attack = std::stod(attack_string);
                        double release = std::stod(release_string);
                        envelope->set_attack_length(attack);
                        envelope->set_release_length(release);
                    }
                    catch (...) {}
                }
            );
            update_inputs();
        }
    );

    this->setLayout(layout);
}





