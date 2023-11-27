#pragma once

#include <type_traits>

namespace ricci::axioms {
namespace impl_ {
template <auto t_op, typename T_Arg_1, typename T_Arg_2>
struct Is_Commutative_ : std::false_type {};
}  // namespace impl_

template <auto t_op, typename T_Arg_1, typename T_Arg_2>
constexpr bool is_commutative = impl_::Is_Commutative_<
    t_op,
    std::remove_cvref_t<T_Arg_1>,
    std::remove_cvref_t<T_Arg_2>
>::value;
}  // namespace ricci::axioms
