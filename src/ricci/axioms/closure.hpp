#pragma once

#include <concepts>
#include <type_traits>

namespace ricci::axioms {
namespace impl_ {
template <auto t_op, typename T_Arg_1, typename T_Arg_2>
struct Is_Closed_ : std::false_type {};

template <auto t_op, typename T_Arg_1, typename T_Arg_2>
requires std::same_as<T_Arg_1, T_Arg_2> and
    std::same_as<T_Arg_1, std::invoke_result_t<decltype(t_op), T_Arg_1, T_Arg_2>>
struct Is_Closed_<t_op, T_Arg_1, T_Arg_2> : std::true_type {};
}  // namespace impl_

template <auto t_op, typename T_Arg_1, typename T_Arg_2>
constexpr bool is_closed = impl_::Is_Closed_<
    t_op,
    std::remove_cvref_t<T_Arg_1>,
    std::remove_cvref_t<T_Arg_2>
>::value;
}  // namespace ricci::axioms
