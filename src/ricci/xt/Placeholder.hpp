#pragma once

#include <iosfwd>
#include <string_view>
#include <type_traits>
#include <utility>

#include <boost/hana/type.hpp>
#include <boost/hana/pair.hpp>

#include "ricci/mp/receive.hpp"
#include "ricci/xt/Result_Of.hpp"

namespace ricci::xt {
template <typename T, typename T_Tag>
struct Placeholder {
    using Result = T;
    using Tag = T_Tag;

    template <typename T_Value>
    constexpr decltype(auto)
    operator = (T_Value&& value) const {
        using boost::hana::pair;
        using boost::hana::type;
        using boost::hana::type_c;
        using ricci::mp::Received;

        return pair<type<T_Tag>, Received<T_Value>>{
            type_c<T_Tag>,
            std::forward<T_Value>(value)
        };
    }
};

template <typename T, typename T_Tag>
std::ostream& operator << (std::ostream& out, Placeholder<T, T_Tag>) {
    return out << T_Tag::name;
}

namespace impl_ {
template <typename T, typename T_Tag>
struct Result_Of_<Placeholder<T, T_Tag>> {
    using type = T;
};
}  // namespace impl_
}  // namespace ricci::xt

#define RICCI_MAKE_PLACEHOLDER_TAG(NAME) \
struct NAME##_Tag { static constexpr std::string_view name = #NAME; }
