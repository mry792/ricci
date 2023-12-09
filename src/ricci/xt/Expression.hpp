#pragma once

#include "ricci/core/operators.hpp"
#include "ricci/xt/Expression.fwd.hpp"
#include "ricci/xt/Operation.hpp"

namespace ricci::xt {
#define RICCI_DEFINE_BINARY_OPERATION(ENTRY_POINT, IMPL) \
template <typename T_Lhs, typename T_Rhs>                \
requires (Expression<T_Lhs> or Expression<T_Rhs>) and    \
requires (Result_Of<T_Lhs> lhs, Result_Of<T_Rhs> rhs) {  \
    IMPL(lhs, rhs);                                      \
}                                                        \
constexpr auto ENTRY_POINT (T_Lhs&& lhs, T_Rhs&& rhs) {  \
    return make_operation<IMPL>(                         \
        std::forward<T_Lhs>(lhs),                        \
        std::forward<T_Rhs>(rhs)                         \
    );                                                   \
}

RICCI_DEFINE_BINARY_OPERATION(operator +, core::operators::add);

#undef RICCI_DEFINE_BINARY_OPERATION
}  // namespace ricci::xt
