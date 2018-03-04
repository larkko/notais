#pragma once

#include <functional>

#include "../lib/util/ringbuffer.hh"

typedef Ring_buffer<std::function<void (), 10> Task_queue;
