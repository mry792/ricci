#ifndef RICCI__AXIOMS__ASSOCIATIVITY_HPP_
#define RICCI__AXIOMS__ASSOCIATIVITY_HPP_

#include <concepts>
#include <functional>
#include <type_traits>

namespace ricci::axioms {
template <auto t_op, typename T_Arg_1, typename T_Arg_2>
struct IsAssociative : std::false_type {};

template <auto t_op, typename T_Arg_1, typename T_Arg_2>
constexpr bool is_associative = IsAssociative<t_op, T_Arg_1, T_Arg_2>::value;

template <std::algebraic T_Arg_1, std::algebraic T_Arg_2>
struct IsAssociative<std::plus<>{}, T_Arg_1, T_Arg_2> : std::true_type {};

template <std::algebraic T_Arg_1, std::algebraic T_Arg_2>
struct IsAssociative<std::multiplies<>{}, T_Arg_1, T_Arg_2> : std::true_type {};
}  // namespace ricci::axioms

#endif  // RICCI__AXIOMS__ASSOCIATIVITY_HPP_
