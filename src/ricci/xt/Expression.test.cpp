
#include "ricci/xt/Expression.hpp"

#include <concepts>
#include <type_traits>

#include "ricci/xt/Constant.hpp"
// #include "ricci/xt/Result_Of.hpp"
#include "ricci/xt/Placeholder.hpp"
#include "ricci/xt/Variable.hpp"
#include "ricci/xt/operators.hpp"

namespace {
template <auto t_variable>
using Type_Of = std::remove_cvref_t<decltype(t_variable)>;
}  // namespace



namespace TEST_CASE_Expression_operators {
using ricci::xt::Constant;
using ricci::xt::Operation;
using ricci::xt::Variable;
using ricci::xt::constant;
using ricci::xt::operators::add;
using ricci::xt::x;
using ricci::xt::x_tag;

constexpr auto lhs = x.as<double>();
constexpr auto rhs = constant<2.1>;

constexpr auto result = lhs + rhs;

static_assert(std::same_as<
    Type_Of<result>,
    Operation<add, Type_Of<lhs>, Type_Of<rhs>>
>);
}  // namespace TEST_CASE_Expression_operators
