#include <string>

#include <QLabel>

class Heading_widget : public QLabel
{
  Q_OBJECT
  public:
    Heading_widget(std::string const & text = "", QWidget * parent = Q_NULLPTR);
};