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
        std::function<std::string (size_t)> get_description,
        std::function<size_t ()> get_index,
        std::function<size_t ()> get_count,
        std::function<void (size_t)> set_index
    );
};