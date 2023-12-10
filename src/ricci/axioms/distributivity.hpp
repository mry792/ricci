#pragma once

#include <type_traits>

namespace ricci::axioms {
namespace impl_ {
template <
    auto t_op_outer, auto t_op_inner,
    typename T_Arg_1, typename T_Arg_2, typename T_Arg_3
>
struct Is_Left_Distributive_ : std::false_type {};

template <
    auto t_op_outer, auto t_op_inner,
    typename T_Arg_1, typename T_Arg_2, typename T_Arg_3
>
struct Is_Right_Distributive_ : std::false_type {};

template <
    auto t_op_outer, auto t_op_inner,
    typename T_Arg_1, typename T_Arg_2, typename T_Arg_3
>
struct Is_Distributive_ : std::false_type {};
}  // namespace impl_

/*!
 * Checks if this identity holds:
 *
 *   a * (b + c) == a * b + a * c
 *
 * for:
 *   t_op_outer =: *
 *   t_op_inner =: +
 *   T_Arg_1 =: a
 *   T_Arg_2 =: b
 *   T_Arg_3 =: c
 */
template <
    auto t_op_outer, auto t_op_inner,
    typename T_Arg_1, typename T_Arg_2, typename T_Arg_3
>
inline constexpr bool is_left_distributive =
    impl_::Is_Left_Distributive_<
        t_op_outer, t_op_inner,
        std::remove_cvref_t<T_Arg_1>,
        std::remove_cvref_t<T_Arg_2>,
        std::remove_cvref_t<T_Arg_3>
    >::value or
    impl_::Is_Distributive_<
        t_op_outer, t_op_inner,
        std::remove_cvref_t<T_Arg_1>,
        std::remove_cvref_t<T_Arg_2>,
        std::remove_cvref_t<T_Arg_3>
    >::value;

/*!
 * Checks if this identity holds:
 *
 *   (b + c) * a == b * a + c * a
 *
 * for:
 *   t_op_outer =: *
 *   t_op_inner =: +
 *   T_Arg_1 =: a
 *   T_Arg_2 =: b
 *   T_Arg_3 =: c
 */
template <
    auto t_op_outer, auto t_op_inner,
    typename T_Arg_1, typename T_Arg_2, typename T_Arg_3
>
inline constexpr bool is_right_distributive =
    impl_::Is_Right_Distributive_<
        t_op_outer, t_op_inner,
        std::remove_cvref_t<T_Arg_1>,
        std::remove_cvref_t<T_Arg_2>,
        std::remove_cvref_t<T_Arg_3>
    >::value or
    impl_::Is_Distributive_<
        t_op_outer, t_op_inner,
        std::remove_cvref_t<T_Arg_1>,
        std::remove_cvref_t<T_Arg_2>,
        std::remove_cvref_t<T_Arg_3>
    >::value;

template <
    auto t_op_outer, auto t_op_inner,
    typename T_Arg_1, typename T_Arg_2, typename T_Arg_3
>
inline constexpr bool is_distributive =
    (
        impl_::Is_Left_Distributive_<
            t_op_outer, t_op_inner,
            std::remove_cvref_t<T_Arg_1>,
            std::remove_cvref_t<T_Arg_2>,
            std::remove_cvref_t<T_Arg_3>
        >::value and
        impl_::Is_Right_Distributive_<
            t_op_outer, t_op_inner,
            std::remove_cvref_t<T_Arg_1>,
            std::remove_cvref_t<T_Arg_2>,
            std::remove_cvref_t<T_Arg_3>
        >::value
    ) or
    impl_::Is_Distributive_<
        t_op_outer, t_op_inner,
        std::remove_cvref_t<T_Arg_1>,
        std::remove_cvref_t<T_Arg_2>,
        std::remove_cvref_t<T_Arg_3>
    >::value;
}  // namespace ricci::axioms
