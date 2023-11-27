#pragma once

#include <type_traits>
#include <utility>

namespace ricci::mp {
namespace impl_ {
template <typename T>
struct Remove_RValue_Reference_ {
    using type = T;
};

template <typename T>
struct Remove_RValue_Reference_<T&&> {
    using type = T;
};
}  // namespace impl_

template <typename T>
using Remove_RValue_Reference = typename impl_::Remove_RValue_Reference_<T>::type;

template <typename T>
using Received = std::remove_cv_t<Remove_RValue_Reference<T>>;

template <typename T>
constexpr Received<T> receive (T&& t) {
    return std::forward<T>(t);
}
}  // namespace ricci::mp
