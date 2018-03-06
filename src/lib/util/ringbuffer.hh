#pragma once

#include <array>
#include <atomic>
#include <cstddef>

/*A single producer, single consumer ring buffer.
  Pushed items stay as they are in the buffer until overriden by newly
  pushed items.*/
template<typename Type, size_t Size>
class Ring_buffer
{
  public:
    Ring_buffer(Type const & default_value);
    static constexpr size_t size();
    /*Performs function for the top item and removes it from the buffer.
      Returns true if successful (at least one item existed in the buffer)*/
    template <typename Function>
    bool pop(Function function);
    /*Performs function for the top item without removing it from the buffer.
      Returns true if successful (at least one item existed in the buffer)*/
    template <typename Function>
    bool top(Function function);
    /*Pushes an item to the buffer. Returns true if successful (buffer had
      room for at least one more item).*/
    bool push(Type const & item);
  private:
    bool is_empty(size_t head, size_t tail) const;
    bool is_full(size_t head, size_t tail) const;
    size_t next_index(size_t index) const;
    std::array<Type, Size> m_data;
    std::atomic<size_t> m_head_index;
    std::atomic<size_t> m_tail_index;
};

template<typename Type, size_t Size>
Ring_buffer<Type, Size>::Ring_buffer(Type const & default_value)
    : m_head_index{0},
      m_tail_index{0}
{
    for(size_t i = 0; i < m_data.size(); ++i)
    {
        m_data[i] = default_value;
    }
}

template<typename Type, size_t Size>
constexpr size_t Ring_buffer<Type, Size>::size()
{
    return Size;
}

template<typename Type, size_t Size>
template<typename Function>
bool Ring_buffer<Type, Size>::pop(Function function)
{
    size_t head = m_head_index.load();
    size_t tail = m_tail_index.load();
    if(is_empty(head, tail))
    {
        return false;
    }
    else
    {
        function(m_data[head]);
        size_t next = next_index(head);
        m_head_index.store(next);
        return true;
    }
}

template<typename Type, size_t Size>
template<typename Function>
bool Ring_buffer<Type, Size>::top(Function function)
{
    size_t head = m_head_index.load();
    size_t tail = m_tail_index.load();
    if(is_empty(head, tail))
    {
        return false;
    }
    else
    {
        function(m_data[head]);
        return true;
    }
}

template<typename Type, size_t Size>
bool Ring_buffer<Type, Size>::push(Type const & item)
{
    size_t head = m_head_index.load();
    size_t tail = m_tail_index.load();
    if(is_full(head, tail))
    {
        return false;
    }
    else
    {
        size_t next = next_index(tail);
        m_data[next] = item;
        m_tail_index.store(next);
        return true;
    }
}

template<typename Type, size_t Size>
bool Ring_buffer<Type, Size>::is_empty(size_t head, size_t tail) const
{
    return head == tail;
}

template<typename Type, size_t Size>
bool Ring_buffer<Type, Size>::is_full(size_t head, size_t tail) const
{
    return head == next_index(tail);
}

template<typename Type, size_t Size>
size_t Ring_buffer<Type, Size>::next_index(size_t index) const
{
    return (index == (Size - 1)) ? 0 : (index + 1);
}

