#pragma once

#include <utility>

namespace ricci::mp {
namespace impl_ {
template <typename T> struct Received_      { using type = T; };
template <typename T> struct Received_<T&&> { using type = T; };
}  // namespace impl_

template <typename T>
using Received = typename impl_::Received_<T>::type;

template <typename T>
constexpr Received<T> receive (T&& t) {
    return std::forward<T>(t);
}
}  // namespace ricci::mp
