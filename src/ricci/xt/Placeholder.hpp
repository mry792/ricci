#ifndef RICCI__XT__PLACEHOLDER_HPP_
#define RICCI__XT__PLACEHOLDER_HPP_

#include <string_view>
#include <type_traits>
#include <utility>

#include <boost/hana/type.hpp>
#include <boost/hana/pair.hpp>

#include "ricci/mp/receive.hpp"
#include "ricci/xt/Expr_Kind.hpp"
#include "ricci/xt/Result_Of.hpp"

namespace ricci::xt {
template <typename T, typename T_Tag>
struct Placeholder {
    using Result = T;
    using Tag = T_Tag;

    template <typename T_Expression>
    constexpr decltype(auto)
    operator = (T_Expression&& expr) const {
        using boost::hana::make_pair;
        using boost::hana::type_c;
        using ricci::mp::receive;

        return make_pair(type_c<Placeholder>, receive<T_Expression>(expr));
    }
};

namespace impl_ {
template <typename T, typename T_Tag>
struct Kind_Of_<Placeholder<T, T_Tag>> {
    static constexpr Expr_Kind value = Expr_Kind::placeholder;
};

template <typename T, typename T_Tag>
struct Result_Of_<Placeholder<T, T_Tag>> {
    using type = T;
};
}  // namespace impl_
}  // namespace ricci::xt

#define RICCI_MAKE_TAG(NAME) struct NAME##_Tag { static constexpr std::string_view name = #NAME; }

#endif  // RICCI__XT__PLACEHOLDER_HPP_
