#pragma once

#include <functional>
#include <utility>

#include <boost/hana/functional/on.hpp>
#include <boost/hana/unpack.hpp>

#include "ricci/xt/Expr_Kind.hpp"
#include "ricci/xt/Operation.hpp"

namespace ricci::xt {
struct Transform {
    template <typename T_Expr, typename T_XForm>
    constexpr decltype(auto)
    operator () (T_Expr&& expr, T_XForm&& xform) const {
        if constexpr (std::is_invocable_v<T_XForm, T_Expr>) {
            return std::forward<T_XForm>(xform)(std::forward<T_Expr>(expr));
        } else if constexpr (kind_of<std::remove_cvref_t<T_Expr>> == Expr_Kind::operation) {
            using boost::hana::on;
            using boost::hana::unpack;
            return unpack(
                std::forward<T_Expr>(expr).args(),
                on(make_operation<expr.op()>, std::forward<T_XForm>(xform))
            );
        } else {
            return std::forward<T_Expr>(expr);
        }
    }
};
inline constexpr Transform transform{};
}  // namespace ricci::xt
