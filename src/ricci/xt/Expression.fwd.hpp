#pragma once

#include <type_traits>

namespace ricci::xt {
namespace impl_ {
template <typename T> struct Is_Expression_ : std::false_type {};
}  // namespace impl_

// template <typename T>
// constexpr bool is_expression = impl_::Is_Expression_<T>::value;

template <typename T>
concept Expression = impl_::Is_Expression_<std::remove_cvref_t<T>>::value;
}  // namespace ricci::xt
