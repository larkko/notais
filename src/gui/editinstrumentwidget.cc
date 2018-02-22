#include "editinstrumentwidget.hh"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTabWidget>
#include <QDial>

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

    QWidget * general_tab = new Edit_instrument_general_tab_widget(instrument);
    tabs->addTab(general_tab, "general");
    QLabel * instrument_tab = new QLabel("instrument tab");
    tabs->addTab(instrument_tab, "instrument");
    QLabel * effects_tab = new QLabel("effects tab");
    tabs->addTab(effects_tab, "effects");

    this->setLayout(layout);
}

Edit_instrument_general_tab_widget::Edit_instrument_general_tab_widget
(
    std::shared_ptr<Adjustable_audio_source> instrument,
    QWidget * parent
)
    : QWidget(parent),
      m_instrument(instrument)
{
    QVBoxLayout * layout = new QVBoxLayout();

    QHBoxLayout * volume_layout = new QHBoxLayout();
    layout->addLayout(volume_layout);
    QLabel * volume_label = new QLabel("volume: ");
    volume_layout->addWidget(volume_label);
    QDial * volume_dial = new QDial();
    volume_layout->addWidget(volume_dial);
    volume_dial->setMinimum(0);
    volume_dial->setMaximum(100);
    volume_dial->setValue(volume_dial->maximum() * m_instrument->volume());

    QObject::connect
    (
        volume_dial,
        &QDial::sliderMoved,
        this,
        [=](int position)
        {
            m_instrument->set_volume(float(position)/float(volume_dial->maximum()));
        }
    );

    this->setLayout(layout);
}









