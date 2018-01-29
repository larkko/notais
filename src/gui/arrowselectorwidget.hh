#pragma once

#include <functional>
#include <string>
#include <cstddef>

#include <QWidget>

class Arrow_selector_widget : public QWidget
{
  Q_OBJECT
  public:
    Arrow_selector_widget
    (
        std::function<std::string ()> get_description,
        std::function<size_t ()> get_index,
        std::function<size_t ()> get_count,
        std::function<void (size_t)> set_index
    );
  private:
    std::function<std::string ()> m_get_description;
    std::function<size_t ()> m_get_index;
    std::function<size_t ()> m_get_count;
    std::function<void (size_t)> m_set_index;
};