#pragma once

#include <typeindex>

namespace util
{

template<typename Pointer>
std::type_index underlying_type(Pointer pointer);

}

#include "util.tt"
