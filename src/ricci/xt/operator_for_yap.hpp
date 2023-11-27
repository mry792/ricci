#pragma once

#include <boost/yap/algorithm_fwd.hpp>

#include "ricci/xt/operators.hpp"

namespace ricci::xt {
namespace impl_ {
template <boost::yap::expr_kind t_expr_kind> struct Operator_For_Yap_;
// expr_ref = 0,
// terminal = 1,

#define RICCI_MAKE_OPERATOR_MAP_ELEMENT(ENUM_VALUE, CALLABLE) \
template <>                                                   \
struct Operator_For_Yap_<boost::yap::expr_kind::ENUM_VALUE> {    \
    inline constexpr auto op = operators::CALLABLE;           \
}

// assignment operators

RICCI_MAKE_OPERATOR_MAP_ELEMENT(assign,            assign);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(plus_assign,       add_assign);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(minus_assign,      subtract_assign);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(multiplies_assign, multiply_assign);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(divides_assign,    divide_assign);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(modulus_assign,    modulo_assign);

RICCI_MAKE_OPERATOR_MAP_ELEMENT(bitwise_and_assign, bit_and_assign);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(bitwise_or_assign,  bit_or_assign);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(bitwise_xor_assign, bit_xor_assign);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(shift_left_assign,  shift_left_assign);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(shift_right_assign, shift_right_assign);

// increment/decrement operators

RICCI_MAKE_OPERATOR_MAP_ELEMENT(pre_inc,  pre_inc);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(pre_dec,  pre_dec);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(post_inc, post_inc);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(post_dec, post_dec);

// arithmetic operators

RICCI_MAKE_OPERATOR_MAP_ELEMENT(unary_plus,  unary_plus);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(negate,      unary_minus);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(plus,        add);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(minus,       subtract);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(multiplies,  multiply);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(divides,     divide);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(modulus,     modulo);

// bitwise operators

RICCI_MAKE_OPERATOR_MAP_ELEMENT(complement,  bit_not);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(bitwise_and, bit_and);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(bitwise_or,  bit_or);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(bitwise_xor, bit_xor);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(shift_left,  shift_left);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(shift_right, shift_right);

// logical operators

RICCI_MAKE_OPERATOR_MAP_ELEMENT(logical_not, logical_not);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(logical_and, logical_and);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(logical_or,  logical_or);

// comparison operators

RICCI_MAKE_OPERATOR_MAP_ELEMENT(equal_to,      equal_to);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(not_equal_to,  not_equal_to);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(less,          less);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(greater,       greater);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(less_equal,    less_equal);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(greater_equal, greater_equal);

// member access operators

RICCI_MAKE_OPERATOR_MAP_ELEMENT(subscript,   subscript);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(dereference, indirect);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(address_of,  address_of);
// RICCI_MAKE_OPERATOR_MAP_ELEMENT(mem_ptr,     mem_ptr);

// other operators

RICCI_MAKE_OPERATOR_MAP_ELEMENT(call,    call);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(comma,   comma);
RICCI_MAKE_OPERATOR_MAP_ELEMENT(if_else, conditional);

#undef RICCI_MAKE_OPERATOR_MAP_ELEMENT
}  // namespace impl_

template <boost::yap::expr_kind t_expr_kind>
using Operator_For_Yap = typename impl_::Operator_For_Yap_<t_expr_kind>::type

template <boost::yap::expr_kind t_expr_kind>
inline constexpr auto operator_for_yap = impl_::Operator_For_Yap_<t_expr_kind>::type{};
}  // namespace ricci::xt
