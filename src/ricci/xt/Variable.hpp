#pragma once

#include <type_traits>

#include "ricci/concepts/Expression.hpp"
#include "ricci/xt/Result_Of.hpp"

namespace ricci::xt {
template <typename T, typename T_Tag>
struct Variable {
    using Result = T;
    using Tag = T_Tag;
};

namespace impl_ {
template <typename T, typename T_Tag>
struct Result_Of_<Variable<T, T_Tag>> {
    using type = T;
};
}  // namespace impl_
}  // namespace ricci::xt

namespace ricci::concepts::impl_ {
template <typename T, typename T_Tag>
struct Is_Expression_<xt::Variable<T, T_Tag>> : std::true_type {};
}  // namespace ricci::concepts::impl_
