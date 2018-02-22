#include "editinstrumentwidget.hh"

#include <QVBoxLayout>
#include <QLabel>
#include <QTabWidget>

Edit_instrument_widget::Edit_instrument_widget
(
    std::shared_ptr<Adjustable_audio_source> instrument,
    QWidget * parent
)
    : QWidget(parent)
{
    QVBoxLayout * layout = new QVBoxLayout();

    QTabWidget * tabs = new QTabWidget();
    layout->addWidget(tabs);

    QLabel * general_tab = new QLabel("general tab");
    tabs->addTab(general_tab, "general");
    QLabel * instrument_tab = new QLabel("instrument tab");
    tabs->addTab(instrument_tab, "instrument");
    QLabel * effects_tab = new QLabel("effects tab");
    tabs->addTab(effects_tab, "effects");

    this->setLayout(layout);
}
