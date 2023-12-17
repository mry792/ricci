#pragma once

#include "ricci/axioms.hpp"
#include "ricci/core/operators.hpp"

namespace ricci::concepts::algebra {
//
// one operation (Magmas and Groups)
//

template <typename T, auto t_op>
concept Magma = axioms::is_closed<t_op, T, T>;

// Quasigroup? (Not sure how to handle "divisibilty".)

template <typename T, auto t_op>
concept Unital_Magma =
    axioms::is_closed<t_op, T, T> and
    axioms::has_identity<t_op, T, T>;

template <typename T, auto t_op>
concept Semigroup =
    axioms::is_closed<t_op, T, T> and
    axioms::is_associative<t_op, T, T>;

template <typename T, auto t_op>
concept Loop =
    axioms::is_closed<t_op, T, T> and
    axioms::has_inverse<t_op, T> and
    axioms::has_identity<t_op, T, T>;

// Associative quasigroup?

template <typename T, auto t_op>
concept Monoid =
    axioms::is_closed<t_op, T, T> and
    axioms::is_associative<t_op, T, T> and
    axioms::has_identity<t_op, T, T>;

template <typename T, auto t_op>
concept Group =
    axioms::is_closed<t_op, T, T> and
    axioms::is_associative<t_op, T, T> and
    axioms::has_identity<t_op, T, T> and
    axioms::has_inverse<t_op, T>;

template <typename T, auto t_op>
concept Abelian_Group =
    Group<T, t_op> and
    axioms::is_commutative<t_op, T, T>;

//
// two operations
//

template <
    typename T,
    auto t_op_add = core::operators::add,
    auto t_op_multiply = core::operators::multiply
>
concept Ring =
    Abelian_Group<T, t_op_add> and
    Monoid<T, t_op_multiply> and
    is_distributive<t_op_multiply, t_op_add, T, T, T>;

template <
    typename T,
    auto t_op_add = core::operators::add,
    auto t_op_multiply = core::operators::multiply
>
concept Field =
    Abelian_Group<T, t_op_add> and
    Abelian_Group<T, t_op_add> and
    is_distributive<t_op_multiply, t_op_add, T, T, T>;
}  // namespace ricci::concepts::algebra
