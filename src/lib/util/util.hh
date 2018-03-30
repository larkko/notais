#pragma once

#include <typeindex>

namespace util
{

template<typename Pointer>
std::type_index underlying_type(Pointer pointer);

template<typename Pointer>
std::type_index underlying_type(Pointer pointer)
{
    return std::type_index(typeid(*pointer));
}

template <typename Number>
class Point
{
  public:
    Point(Number x, Number y) : m_x(x), m_y(y) {}
    Number x() const { return m_x; }
    Number y() const { return m_y; }
  private:
    Number m_x;
    Number m_y;
};

template <typename Number>
class Rectangle
{
  public:
    Rectangle(Point<Number> first, Point<Number> second)
        : m_first(first), m_second(second) {}
    bool contains(Point<Number> point) const
    {
        Number left_x = std::min(m_first.x(), m_second.x());
        Number right_x = std::max(m_first.x(), m_second.x());
        Number top_y = std::min(m_first.y(), m_second.y());
        Number bottom_y = std::max(m_first.y(), m_second.y());
        Number x = point.x();
        Number y = point.y();
        return (x >= left_x) && (x <= right_x)
            && (y >= top_y) && (y <= bottom_y);
    }
  private:
    Point<Number> m_first;
    Point<Number> m_second;
};

}
