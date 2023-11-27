#pragma once

#include <iosfwd>

#include "ricci/xt/Result_Of.hpp"

namespace ricci::xt {
template <auto t_value>
struct Constant {
    using Result = decltype(t_value);
    static constexpr Result value = t_value;

    constexpr operator Result () const { return t_value; }
};

template <auto t_value>
static constexpr auto constant = Constant<t_value>{};

template <auto t_value>
std::ostream& operator << (std::ostream& out, Constant<t_value>) {
    return out << t_value;
}

namespace impl_ {
template <auto t_value>
struct Result_Of_<Constant<t_value>> {
    using type = typename Constant<t_value>::Result;
};
}  // namespace impl_
}  // namespace ricci::xt
