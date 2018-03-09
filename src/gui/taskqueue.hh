#pragma once

#include <functional>
#include <atomic>

#include "../lib/util/ringbuffer.hh"

typedef Ring_buffer<std::function<void ()>, 10> Task_queue;

/*Sends the specified action to a task queue and waits until it's
  been performed to return. Only use for fast actions.*/
template<typename Function>
void atomic_perform(Task_queue & queue, Function function)
{
    std::atomic<bool> flag{false};
    queue.push
    ([=, &flag]()
    {
        function();
        flag.store(true);
    });
    while(!flag.load()) {}
}
