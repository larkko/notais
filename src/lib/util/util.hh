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

}
