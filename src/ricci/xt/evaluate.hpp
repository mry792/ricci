#pragma once

#include <utility>

#include <boost/hana/find.hpp>
#include <boost/hana/functional/on.hpp>
#include <boost/hana/map.hpp>
#include <boost/hana/type.hpp>
#include <boost/hana/unpack.hpp>

#include "ricci/xt/Constant.hpp"
#include "ricci/xt/Expr_Kind.hpp"
#include "ricci/xt/Operation.hpp"
#include "ricci/xt/Placeholder.hpp"
#include "ricci/xt/transform.hpp"

namespace ricci::xt {
template <typename T_Sub_Map>
struct Evaluator {
    T_Sub_Map sub_map_;

    // // value or constant
    // template <typename T_Value>
    // requires
    //     kind_of<T_Value> == Expr_Kind::value or
    //     kind_of<T_Value> == Expr_Kind::constant
    // constexpr decltype(auto) operator () (T_Value&& value) const {
    //     return std::forward<T_Value>(value);
    // }

    // placeholder
    template <typename T_Placeholder>
    requires kind_of<T_Placeholder> == Expr_Kind::placeholder
    constexpr decltype(auto) operator () (T_Placeholder) const {
        using boost::hana::find;
        using boost::hana::type_;
        constexpr auto key = type_c<T_Placeholder>;
        return find(sub_map_, key).value();
    }

    // operation
    template <typename T_Expr>
    requires kind_of<std::remove_cvref_t<T_Expr>> == Expr_Kind::operation
    constexpr auto operator () (T_Expr&& expr) const {
        using boost::hana::on;
        using boost::hana::unpack;

        return unpack(
            std::forward<T_Expr>(expr).args(),
            on(std::forward<T_Expr>(expr).op(), *this)
        );
    }
};

struct Evaluate {
    template <typename... T_Substitutions>
    constexpr auto operator () (T_Substitutions&&... substitutions) const {
        using boost::hana::make_map
        return [evaluator = Evaluator{make_map(
            std::forward<T_Substitutions>(substitutions)...
        )}] (auto&& expr) {
            return transform(expr, evaluator);
        };
    }
};
inline constexpr Evaluate evaluate{};
}  // namespace ricci::xt
