#include "edittuningwidget.hh"

#include <QLabel>

#include "../lib/util/util.hh"

Edit_tuning_widget::Edit_tuning_widget
(
    std::shared_ptr<Tuning> tuning,
    QWidget *parent
)
    : QWidget(parent)
{
    new QLabel("edit tuning widget", this);
}
