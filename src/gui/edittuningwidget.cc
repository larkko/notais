#include "edittuningwidget.hh"

#include <QLabel>

Edit_tuning_widget::Edit_tuning_widget
(
    std::shared_ptr<Tuning> tuning,
    QWidget *parent
)
    : QWidget(parent)
{
    new QLabel("edit tuning widget", this);
}
