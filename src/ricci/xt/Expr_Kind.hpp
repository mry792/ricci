#pragma once

namespace ricci::xt {
enum class Expr_Kind {
    value,
    constant,
    placeholder,
    operation,
};

namespace impl_ {
template <typename T>
struct Kind_Of_ {
    static constexpr Expr_Kind value = Expr_Kind::value;
}
}  // namespace impl_

template <typename T>
inline constexpr Expr_Kind kind_of = impl_::Kind_Of_<T>::value;
}  // namespace ricci::xt