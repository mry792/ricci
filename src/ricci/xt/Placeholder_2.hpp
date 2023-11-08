#ifndef RICCI__XT__PLACEHOLDER_2_HPP_
#define RICCI__XT__PLACEHOLDER_2_HPP_

#include <type_traits>
#include <utility>

#include "ricci/mp/receive.hpp"
#include "ricci/xt/Result_Of.hpp"
#include "ricci/xt/Substitution.hpp"

namespace ricci::xt {
template <typename T, typename T_Tag>
struct Placeholder_2 {
    using Result = T;

    template <typename T_Expression>
    constexpr Substitution<Placeholder_2, Received<T_Expression>>
    operator = (T_Expression&& expr) const {
        return {std::forward<T_Expression>(expr)}
    }
};

namespace impl_ {
template <typename T, typename T_Tag>
struct Result_Of_<Placeholder_2<T, T_Tag>> {
    using type = T;
};
}  // namespace impl_
}  // namespace ricci::xt

#endif  // RICCI__XT__PLACEHOLDER_2_HPP_
