#pragma once

#include <type_traits>

namespace ricci::axioms {
namespace impl_ {
template <auto t_op, typename T_Arg_1, typename T_Arg_2>
struct Identity_;
}  // namespace impl_

template <auto t_op, typename T_Arg_1, typename T_Arg_2>
inline constexpr auto identity = impl_::Identity_<
    t_op,
    std::remove_cvref_t<T_Arg_1>,
    std::remove_cvref_t<T_Arg_2>
>::value;

template <auto t_op, typename T_Arg_1, typename T_Arg_2>
inline constexpr bool has_identity = requires {
    { impl_::Identity_<
        t_op,
        std::remove_cvref_t<T_Arg_1>,
        std::remove_cvref_t<T_Arg_2>
    >::value };
};
}  // namespace ricci::axioms
