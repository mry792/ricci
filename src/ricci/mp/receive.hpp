#pragma once

#include <type_traits>
#include <utility>

namespace ricci::mp {
template <typename T>
using Received = std::remove_rvalue_reference_t<T>;

template <typename T>
constexpr Received<T> receive (T&& t) {
    return std::forward<T>(t);
}
}  // namespace ricci::mp
