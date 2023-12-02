#pragma once

#include <type_traits>
#include <utility>

namespace ricci::mp {
template <typename T, typename T_Tag = void>
struct Member {
    T value_;
    constexpr T&       get_ () &      noexcept { return           value_;  }
    constexpr T const& get_ () const& noexcept { return           value_;  }
    constexpr T&&      get_ () &&     noexcept { return std::move(value_); }
};

template <typename T, typename T_Tag>
requires std::is_empty_v<T>
struct Member<T, T_Tag> {
    constexpr Member () noexcept = default;
    constexpr Member (T) noexcept {}
    constexpr T get_ () const noexcept { return T{}; }
};
}  // namespace ricci::mp
