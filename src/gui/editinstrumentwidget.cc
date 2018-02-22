#include "editinstrumentwidget.hh"

#include <QVBoxLayout>
#include <QLabel>

Edit_instrument_widget::Edit_instrument_widget
(
    std::shared_ptr<Adjustable_audio_source> instrument,
    QWidget * parent
)
    : QWidget(parent)
{
    QVBoxLayout * layout = new QVBoxLayout;

    QLabel * label = new QLabel("edit instrument widget");
    layout->addWidget(label);

    this->setLayout(layout);
}
