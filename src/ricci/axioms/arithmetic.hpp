#pragma once

#include <type_traits>

#include "ricci/axioms/associativity.hpp"
#include "ricci/axioms/commutativity.hpp"
#include "ricci/axioms/identity.hpp"
#include "ricci/concepts/std_ext.hpp"
#include "ricci/core/operators.hpp"
#include "ricci/xt/Constant.hpp"

namespace ricci::axioms::impl_ {
namespace operators = ricci::core::operators;

// associativity

template <concepts::Arithmetic T_Arg_1, concepts::Arithmetic T_Arg_2>
struct Is_Associative_<operators::add, T_Arg_1, T_Arg_2> : std::true_type {};

template <concepts::Arithmetic T_Arg_1, concepts::Arithmetic T_Arg_2>
struct Is_Associative_<operators::multiply, T_Arg_1, T_Arg_2> : std::true_type {};

// commutativity

template <concepts::Arithmetic T_Arg_1, concepts::Arithmetic T_Arg_2>
struct Is_Commutative_<operators::add, T_Arg_1, T_Arg_2> : std::true_type {};

template <concepts::Arithmetic T_Arg_1, concepts::Arithmetic T_Arg_2>
struct Is_Commutative_<operators::multiply, T_Arg_1, T_Arg_2> : std::true_type {};

// identity

template <concepts::Arithmetic T_Arg_1, concepts::Arithmetic T_Arg_2>
struct Identity_<operators::add, T_Arg_1, T_Arg_2> {
    using type = std::common_type_t<T_Arg_1, T_Arg_2>;
    static constexpr xt::Constant<type{0}> value{};
};

template <concepts::Arithmetic T_Arg_1, concepts::Arithmetic T_Arg_2>
struct Identity_<operators::multiply, T_Arg_1, T_Arg_2> {
    using type = std::common_type_t<T_Arg_1, T_Arg_2>;
    static constexpr xt::Constant<type{1}> value{};
};
}  // namespace ricci::axioms::impl_
