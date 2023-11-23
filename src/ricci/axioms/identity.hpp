#ifndef RICCI__AXIOMS__IDENTITY_HPP_
#define RICCI__AXIOMS__IDENTITY_HPP_

#include <type_traits>

#include "ricci/concepts/std_ext.hpp"
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
template <concepts::Arithmetic T_Arg_1, concepts::Arithmetic T_Arg_2>
struct Identity_<xt::operators::add, T_Arg_1, T_Arg_2> {
    using type = std::common_type_t<T_Arg_1, T_Arg_2>;
    static constexpr xt::Constant<type{0}> value{};
};

template <concepts::Arithmetic T_Arg_1, concepts::Arithmetic T_Arg_2>
struct Identity_<xt::operators::multiply, T_Arg_1, T_Arg_2> {
    using type = std::common_type_t<T_Arg_1, T_Arg_2>;
    static constexpr xt::Constant<type{1}> value{};
};
}  // namespace impl_
}  // namespace ricci::axioms

#endif  // RICCI__AXIOMS__IDENTITY_HPP_
