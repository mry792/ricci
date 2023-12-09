#pragma once

#include <string_view>
#include <type_traits>
#include <utility>

#include <boost/hana/pair.hpp>

#include "ricci/mp/receive.hpp"
#include "ricci/xt/Variable.hpp"

namespace ricci::xt {
template <typename T_Tag>
struct Placeholder {
    using Tag = T_Tag;

    template <typename T_Value>
    static constexpr Variable<T_Value, T_Tag> as () {
        return {};
    }

    template <typename T_Value>
    constexpr boost::hana::pair<T_Tag, ricci::mp::Received<T_Value>>
    operator = (T_Value&& value) const {
        return {{}, std::forward<T_Value>(value)};
    }
};

// template <typename T_Tag>
// std::ostream& operator << (std::ostream& out, Placeholder<T_Tag>) {
//     return out << "placeholder<" << T_Tag::name << ">";
// }

#define RICCI_MAKE_PLACEHOLDER(NAME)                                   \
struct NAME##_tag { static constexpr std::string_view name = #NAME; }; \
inline constexpr Placeholder<NAME##_tag> NAME{};

RICCI_MAKE_PLACEHOLDER(x);
}  // namespace ricci::xt
