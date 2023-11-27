#pragma once

#include <concepts>

#include <boost/yap/algorithm_fwd.hpp>

namespace ricci::xt::concepts {
// template <typename T>
// concept Yap_Expression = requires (T expr) {
//     { T::kind } -> std::same_as<boost::yap::expr_kind>;
//     expr.elements;
// };
template <typename T>
concept Yap_Expression = boost::yap::is_expr<T>::value;
}  // namespace ricci::xt::concepts
