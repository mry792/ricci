#ifndef RICCI__AXIOMS__ASSOCIATIVITY_HPP_
#define RICCI__AXIOMS__ASSOCIATIVITY_HPP_

#include <type_traits>

#include "ricci/concepts/std_ext.hpp"
#include "ricci/xt/operators.hpp"

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

namespace impl_ {
template <concepts::Arithmetic T_Arg_1, concepts::Arithmetic T_Arg_2>
struct Is_Commutative_<xt::operators::add, T_Arg_1, T_Arg_2> : std::true_type {};

template <typename T_Arg_1, typename T_Arg_2>
requires std::is_arithmetic_v<T_Arg_1> and std::is_arithmetic_v<T_Arg_2>
struct Is_Commutative_<xt::operators::multiply, T_Arg_1, T_Arg_2> : std::true_type {};
}  // namespace impl_
}  // namespace ricci::axioms

#endif  // RICCI__AXIOMS__ASSOCIATIVITY_HPP_