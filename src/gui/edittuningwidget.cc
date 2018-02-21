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
    new QLabel("edit equal temperament", this);
}
