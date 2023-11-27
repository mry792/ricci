#pragma once

#include <type_traits>

#include "ricci/xt/Result_Of.hpp"
#include "ricci/xt/concepts/Yap_Expression.hpp"

namespace ricci::xt {
namespace impl_ {
using namespace yap = boost::yap

struct Result_Of_Expr_ {
    template <typename T>
    constexpr auto operator () (
        yap::expr_tag<yap::expr_kind::terminal>,
        T&&
    ) {
        return std::declval<
            Result_Of<std::remove_rvalue_reference_t<T>>
        >();
    }

    template <yap::expr_kind t_expr_kind, typename... T_Args>
    constexpr auto operator () (
        yap::expr_tag::<t_expr_kind>,
        T_Args&&... args
    ) {
        return std::declval<std::invoke_result_t<
            Operator_For<t_expr_kind>,
            decltype(
                yap::transform_strict(
                    std::forward<T_Args>(args),
                    *this
                )
            )...
        >>();
    }
};

template <concepts::Yap_Expression T_Expr>
struct Result_Of_<T_Expr> {
    using type = decltype(yap::transform_strict(
        std::declval<T_Expr>(),
        Result_Of_Expr_{}
    ));
};
}  // namespace impl_
}  // namespace ricci::xt
