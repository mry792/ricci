#pragma once

#include <functional>
#include <type_traits>

namespace ricci::axioms {
template <auto t_op, typename T_Arg_1, typename T_Arg_2>
struct IsAssociative : std::false_type {};

template <auto t_op, typename T_Arg_1, typename T_Arg_2>
constexpr bool is_associative = IsAssociative<t_op, T_Arg_1, T_Arg_2>::value;

template <typename T_Arg_1, typename T_Arg_2>
requires
    std::is_arithmetic_v<std::remove_reference_t<T_Arg_1>> and
    std::is_arithmetic_v<std::remove_reference_t<T_Arg_2>>
struct IsAssociative<std::plus<>{}, T_Arg_1, T_Arg_2> : std::true_type {};

template <typename T_Arg_1, typename T_Arg_2>
requires
    std::is_arithmetic_v<std::remove_reference_t<T_Arg_1>> and
    std::is_arithmetic_v<std::remove_reference_t<T_Arg_2>>
struct IsAssociative<std::multiplies<>{}, T_Arg_1, T_Arg_2> : std::true_type {};
}  // namespace ricci::axioms
