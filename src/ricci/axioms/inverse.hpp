#pragma once

#include <type_traits>

#include "ricci/axioms/identity.hpp"

namespace ricci::axioms {
// inverse_operation

namespace impl_ {
template <auto t_op, typename T_Arg_1, typename T_Arg_2>
struct Inverse_Operation_;
}  // namespace impl_

template <auto t_op, typename T_Arg_1, typename T_Arg_2>
inline constexpr auto inverse_operation = impl_::Inverse_Operation_<t_op, T_Arg_1, T_Arg_2>::value;

// inverse_element

namespace impl_ {
template <auto t_op, typename T>
struct Inverse_Element_;
}  // namespace impl_

template <auto t_op>
struct Inverse_Element {
    template <typename T>
    constexpr auto operator () (T const& value) {
        using Impl = impl_::Inverse_Element_<t_op, std::remove_cvref_t<T>>;
        return Impl::apply(value);
    }
};
template <auto t_op>
inline constexpr Inverse_Element<t_op> inverse_element{};

// has_inverse

template <auto t_op, typename T>
inline constexpr bool has_inverse = requires (T const value) {
    impl_::Inverse_Element_<t_op, std::remove_cvref_t<T>>::apply(value);
};
}  // namespace ricci::axioms
