#pragma once

/*!
 * @file
 *
 * This file provides function objects corresponding to most operators in C++.
 * All of them support compile-time execution and can be used as NTTPs.
 */

#include <functional>
#include <string_view>
#include <type_traits>
#include <utility>

#define FWD(X) std::forward<decltype(X)>(X)

#define RICCI_DEFINE_UNARY_PREFIX_OPERATOR(TYPE, VAR, OP) \
struct TYPE {                                             \
    static constexpr std::string_view name = #VAR;        \
                                                          \
    template <typename T>                                 \
    constexpr auto operator () (T&& t)                    \
    noexcept(noexcept(OP FWD(t)))                         \
    -> decltype(OP FWD(t)) {                              \
        return OP FWD(t);                                 \
    }                                                     \
};                                                        \
inline constexpr TYPE VAR{};

#define RICCI_DEFINE_UNARY_POSTFIX_OPERATOR(TYPE, VAR, OP) \
struct TYPE {                                              \
    static constexpr std::string_view name = #VAR;         \
                                                           \
    template <typename T>                                  \
    constexpr auto operator () (T&& t)                     \
    noexcept(noexcept(FWD(t) OP))                          \
    -> decltype(FWD(t) OP) {                               \
        return FWD(t) OP;                                  \
    }                                                      \
};                                                         \
inline constexpr TYPE VAR{};

#define RICCI_DEFINE_BINARY_OPERATOR(TYPE, VAR, OP) \
struct TYPE {                                       \
    static constexpr std::string_view name = #VAR;  \
                                                    \
    template <typename T1, typename T2>             \
    constexpr auto operator () (T1&& t1, T2&& t2)   \
    noexcept(noexcept(FWD(t1) OP FWD(t2)))          \
    -> decltype(FWD(t1) OP FWD(t2)) {               \
        return FWD(t1) OP FWD(t2);                  \
    }                                               \
};                                                  \
inline constexpr TYPE VAR{};

#define RICCI_DEFINE_UNARY_LEFT_FOLD_OPERATOR(TYPE, VAR, OP) \
struct TYPE {                                                \
    static constexpr std::string_view name = #VAR;           \
                                                             \
    template <typename... Ts>                                \
    constexpr auto operator () (Ts&&... ts)                  \
    noexcept(noexcept((... OP FWD(ts))))                     \
    -> decltype((... OP FWD(ts))) {                          \
        return (... OP FWD(ts));                             \
    }                                                        \
};                                                           \
inline constexpr TYPE VAR{};

namespace ricci::core::operators {

// assignment operators

RICCI_DEFINE_BINARY_OPERATOR(Assignment,                assign,             =);
RICCI_DEFINE_BINARY_OPERATOR(Addition_Assignment,       add_assign,         +=);
RICCI_DEFINE_BINARY_OPERATOR(Subtraction_Assignment,    subtract_assign,    -=);
RICCI_DEFINE_BINARY_OPERATOR(Multiplication_Assignment, multiply_assign,    *=);
RICCI_DEFINE_BINARY_OPERATOR(Division_Assignment,       divide_assign,      /=);
RICCI_DEFINE_BINARY_OPERATOR(Modulo_Assignment,         modulo_assign,      %=);

RICCI_DEFINE_BINARY_OPERATOR(Bitwise_And_Assignment,    bit_and_assign,     &=);
RICCI_DEFINE_BINARY_OPERATOR(Bitwise_Or_Assignment,     bit_or_assign,      |=);
RICCI_DEFINE_BINARY_OPERATOR(Bitwise_Xor_Assignment,    bit_xor_assign,     ^=);
RICCI_DEFINE_BINARY_OPERATOR(Left_Shift_Assignment,     left_shift_assign,  <<=);
RICCI_DEFINE_BINARY_OPERATOR(Right_Shift_Assignment,    right_shift_assign, >>=);

// increment/decrement operators

RICCI_DEFINE_UNARY_PREFIX_OPERATOR(Pre_Increment,   pre_inc,  ++);
RICCI_DEFINE_UNARY_PREFIX_OPERATOR(Pre_Decrement,   pre_dec,  --);
RICCI_DEFINE_UNARY_POSTFIX_OPERATOR(Post_Increment, post_inc, ++);
RICCI_DEFINE_UNARY_POSTFIX_OPERATOR(Post_Decrement, post_dec, --);

// arithmetic operators

RICCI_DEFINE_UNARY_PREFIX_OPERATOR(Unary_Plus, unary_plus, +);
using Unary_Minus    = std::negate<>;     inline constexpr Unary_Minus    unary_minus{};
using Addition       = std::plus<>;       inline constexpr Addition       add{};
using Subtraction    = std::minus<>;      inline constexpr Subtraction    subtract{};
using Multiplication = std::multiplies<>; inline constexpr Multiplication multiply{};
using Division       = std::divides<>;    inline constexpr Division       divide{};
using Modulo         = std::modulus<>;    inline constexpr Modulo         modulo{};

RICCI_DEFINE_UNARY_LEFT_FOLD_OPERATOR(Summation, sum,     +);
RICCI_DEFINE_UNARY_LEFT_FOLD_OPERATOR(Product,   product, *);

// bitwise operators

using Bitwise_Not = std::bit_not<>; inline constexpr Bitwise_Not bit_not{};
using Bitwise_And = std::bit_and<>; inline constexpr Bitwise_And bit_and{};
using Bitwise_Or  = std::bit_or<>;  inline constexpr Bitwise_Or  bit_or{};
using Bitwise_Xor = std::bit_xor<>; inline constexpr Bitwise_Xor bit_xor{};
RICCI_DEFINE_BINARY_OPERATOR(Bitwise_Left_Shift,  shift_left,  <<);
RICCI_DEFINE_BINARY_OPERATOR(Bitwise_Right_Shift, shift_right, >>);

// logical operators

using Logical_Not = std::logical_not<>; inline constexpr Logical_Not logical_not{};
using Logical_And = std::logical_and<>; inline constexpr Logical_And logical_and{};
using Logical_Or  = std::logical_or<>;  inline constexpr Logical_Or  logical_or{};

// comparison operators

using Equal_To      = std::ranges::equal_to;      inline constexpr Equal_To      equal_to{};
using Not_Equal_To  = std::ranges::not_equal_to;  inline constexpr Not_Equal_To  not_equal_to{};
using Less          = std::ranges::less;          inline constexpr Less          less{};
using Greater       = std::ranges::greater;       inline constexpr Greater       greater{};
using Less_Equal    = std::ranges::less_equal;    inline constexpr Less_Equal    less_equal{};
using Greater_Equal = std::ranges::greater_equal; inline constexpr Greater_Equal greater_equal{};
RICCI_DEFINE_BINARY_OPERATOR(Three_Way_Comparison, three_way_compare, <=>);

// member access operators

struct Subscript {
    static constexpr std::string_view name = "subscript";

    #define EXPR FWD(host)[FWD(arg)]

    template <typename T_Host, typename T_Arg>
    constexpr auto operator () (T_Host&& host, T_Arg&& arg)
    noexcept(noexcept(EXPR)) -> decltype(EXPR) {
        return EXPR;
    }

    #undef EXPR
};
inline constexpr Subscript subscript{};

RICCI_DEFINE_UNARY_PREFIX_OPERATOR(Indirection, indirect,   *);
RICCI_DEFINE_UNARY_PREFIX_OPERATOR(Address_Of,  address_of, &);
// member-of-pointer operator? "->"
// pointer-to-member-of-pointer operator? "->*"

// other operators

struct Call {
    static constexpr std::string_view name = "call";

    template <typename T_Func, typename... T_Args>
    constexpr auto operator () (T_Func&& func, T_Args&&... args)
    noexcept(std::is_nothrow_invocable_v<T_Func, T_Args...>)
    -> decltype(FWD(func)(FWD(args)...)) {
        return FWD(func)(FWD(args)...);
    }
};
inline constexpr Call call{};

struct Comma {
    static constexpr std::string_view name = "comma";

    template <typename T1, typename T2>
    constexpr auto operator () (T1&& t1, T2&& t2)
    noexcept(noexcept(FWD(t1) , FWD(t2)))
    -> decltype(FWD(t1) , FWD(t2)) {
        return FWD(t1) , FWD(t2);
    }
};
inline constexpr Comma comma{};

struct Conditional {
    static constexpr std::string_view name = "conditional";

    template <typename T_Cond, typename T_True, typename T_False>
    constexpr auto
    operator () (T_Cond&& cond, T_True&& true_, T_False&& false_)
    noexcept(noexcept(FWD(cond) ? FWD(true_) : FWD(false_)))
    -> decltype(FWD(cond) ? FWD(true_) : FWD(false_)) {
        return FWD(cond) ? FWD(true_) : FWD(false_);
    }
};
inline constexpr Conditional conditional{};

// special operators

// casts?
// new/delete?
// sizeof?
// typeid?
// noexcept?
// alignof?

// custom "operators"

struct Invoke {
    static constexpr std::string_view name = "invoke";

    template <typename T_Func, typename... T_Args>
    constexpr auto operator () (T_Func&& func, T_Args&&... args)
    noexcept(std::is_nothrow_invocable_v<T_Func, T_Args...>)
    -> std::invoke_result_t<T_Func, T_Args...> {
        return std::invoke(FWD(func), FWD(args)...);
    }
};
inline constexpr Invoke invoke{};
}  // namespace ricci::core::operators

#undef FWD
#undef RICCI_DEFINE_UNARY_PREFIX_OPERATOR
#undef RICCI_DEFINE_UNARY_POSTFIX_OPERATOR
#undef RICCI_DEFINE_BINARY_OPERATOR
#undef RICCI_DEFINE_UNARY_LEFT_FOLD_OPERATOR
