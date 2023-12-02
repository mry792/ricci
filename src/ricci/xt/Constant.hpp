#pragma once

#include "ricci/xt/Constant.hpp"
#include "ricci/xt/Expr_Kind.hpp"
#include "ricci/xt/Result_Of.hpp"

namespace ricci::xt {
template <auto t_value>
struct Constant {
    using Result = decltype(t_value);
    static constexpr Result value = t_value;

    constexpr operator Result () { return t_value; }
};

template <auto t_value>
static constexpr auto constant = Constant<t_value>{};

namespace impl_ {
template <auto t_value>
struct Kind_Of_<Constant<t_value>> {
    static constexpr Expr_Kind value = Expr_Kind::constant;
};

template <auto t_value>
struct Result_Of_<Constant<t_value>> {
    using type = typename Constant<t_value>::Result;
};
}  // namespace impl_
}  // namespace ricci::xt
