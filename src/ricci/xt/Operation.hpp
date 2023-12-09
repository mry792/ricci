#pragma once

#include <type_traits>
#include <utility>

#include <boost/hana/basic_tuple.hpp>

#include "ricci/mp/Member.hpp"
#include "ricci/mp/receive.hpp"
#include "ricci/xt/Expr_Kind.hpp"
#include "ricci/xt/Result_Of.hpp"

namespace ricci::xt {
template <auto t_op, typename... T_Args>
struct Operation : ricci::mp::Member<boost::hana::basic_tuple<T_Args...>> {
  public:
    using Operator = decltype(t_op);
    using Arguments = boost::hana::basic_tuple<T_Args...>;
    using Result = std::invoke_result_t<Operator, Result_Of<T_Args>...>;

  private:
    using Args_Member = ricci::mp::Member<Arguments>;
    // static_assert(std::is_empty_v<Operator>, "Operator `t_op` must be an empty type.");

  public:
    using Args_Member::Args_Member;

    constexpr Operator op () const { return t_op; }

    constexpr Arguments&       args () &      { return static_cast<Args_Member&      >(*this).get_(); }
    constexpr Arguments const& args () const& { return static_cast<Args_Member const&>(*this).get_(); }
    constexpr Arguments&&      args () &&     { return static_cast<Args_Member&&     >(*this).get_(); }
};

template <auto t_op>
struct Make_Operation {
    template <typename... T_Args>
    constexpr auto operator () (T_Args&&... args) const {
        using Operation_Type = Operation<t_op, std::remove_cvref_t<T_Args>...>;
        return Operation_Type{
            typename Operation_Type::Arguments{
                std::forward<T_Args>(args)...
            }
        };
    }
};
template <auto t_op>
inline constexpr Make_Operation<t_op> make_operation{};

namespace impl_ {
template <auto t_op, typename... T_Args>
struct Kind_Of_<Operation<t_op, T_Args...>> {
    static constexpr Expr_Kind value = Expr_Kind::operation;
};

template <auto t_op, typename... T_Args>
struct Result_Of_<Operation<t_op, T_Args...>> {
    using type = typename Operation<t_op, T_Args...>::Result;
};
}  // namespace impl_
}  // namespace ricci::xt
