#ifndef RICCI__AXIOMS__IDENTITY_HPP_
#define RICCI__AXIOMS__IDENTITY_HPP_

#include <type_traits>

#include "ricci/xt/Constant.hpp"
#include "ricci/xt/operators.hpp"

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

namespace impl_ {
template <typename T_Arg_1, typename T_Arg_2>
requires std::is_arithmetic_v<T_Arg_1> and std::is_arithmetic_v<T_Arg_2>
struct Identity_<xt::operators::add, T_Arg_1, T_Arg_2> {
    inline constexpr xt::Constant<0> value{};
};

template <typename T_Arg_1, typename T_Arg_2>
requires std::is_arithmetic_v<T_Arg_1> and std::is_arithmetic_v<T_Arg_2>
struct Identity_<xt::operators::subtract, T_Arg_1, T_Arg_2> {
    inline constexpr xt::Constant<0> value{};
};

template <typename T_Arg_1, typename T_Arg_2>
requires std::is_arithmetic_v<T_Arg_1> and std::is_arithmetic_v<T_Arg_2>
struct Identity_<xt::operators::multiply, T_Arg_1, T_Arg_2> {
    inline constexpr xt::Constants<1> value{};
};

template <typename T_Arg_1, typename T_Arg_2>
requires std::is_arithmetic_v<T_Arg_1> and std::is_arithmetic_v<T_Arg_2>
struct Identity_<xt::operators::divide, T_Arg_1, T_Arg_2> {
    inline constexpr xt::Constants<1> value{};
};
}  // namespace impl_
}  // namespace ricci::axioms

#endif  // RICCI__AXIOMS__IDENTITY_HPP_
