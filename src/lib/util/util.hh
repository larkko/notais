#pragma once

#include <typeindex>
#include <limits>

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
Number sign(Number number)
{
    return (number < 0) ? -1 : 1;
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
class Line
{
  public:
    Line(Point<Number> first, Point<Number> second)
        : m_first((first.x() < second.x()) ? first : second),
          m_second((first.x() < second.x()) ? second : first) {}
    Point<Number> first() const { return m_first; }
    Point<Number> second() const { return m_second; }
    Number slope() const
    {
        Number x_diff = m_second.x() - m_first.x();
        Number y_diff = m_second.y() - m_first.y();
        return (x_diff == 0)
             ? std::numeric_limits<Number>::max() * sign<Number>(y_diff)
             : y_diff / x_diff;
    }
    Number y_when_x_is(Number x) const
    {
        return m_first.y() + (x - m_first.x()) * slope();
    }
    Number x_when_y_is(Number y) const
    {
        return m_first.x() + (y - m_first.y()) * (1 / slope());
    }
  private:
    Point<Number> m_first;
    Point<Number> m_second;
};

template <typename Number>
class Rectangle
{
  public:
    Rectangle(Point<Number> first, Point<Number> second)
        : m_first(first), m_second(second) {}
    Number left_x() const { return std::min(m_first.x(), m_second.x()); }
    Number right_x() const { return std::max(m_first.x(), m_second.x()); }
    Number top_y() const { return std::min(m_first.y(), m_second.y()); }
    Number bottom_y() const { return std::max(m_first.y(), m_second.y()); }
    bool contains(Point<Number> point) const
    {
        Number x = point.x();
        Number y = point.y();
        return (x >= left_x()) && (x <= right_x())
            && (y >= top_y()) && (y <= bottom_y());
    }
    bool contains(Line<Number> line) const
    {
        bool contains_end_point
            = contains(line.first()) || contains(line.second());
        Number left_y = line.y_when_x_is(left_x());
        Number right_y = line.y_when_x_is(right_x());
        if(line.slope() == 0)
        {
            bool is_between_end_points = line.first().x() <= left_x()
                                      && line.second().x() >= right_x()
                                      && line.first().y() >= top_y()
                                      && line.first().y() <= bottom_y();
            return contains_end_point || is_between_end_points;
        }
        else
        {
            Number top_x = line.x_when_y_is(top_y());
            Number bottom_x = line.x_when_y_is(bottom_y());
            bool touches_edge = (left_y <= top_y() && left_y >= bottom_y())
                             || (right_y <= top_y() && right_y >= bottom_y())
                             || (top_x >= left_x() && top_x <= right_x())
                             || (bottom_x >= left_x() && bottom_x <= right_x());
            return contains_end_point || touches_edge;
        }
    }
    Point<Number> first() const { return m_first; }
    Point<Number> second() const { return m_second; }
  private:
    Point<Number> m_first;
    Point<Number> m_second;
};

}
