#pragma once

#include <functional>
#include <type_traits>

namespace ricci::xt::operators {

//
// Arithmetic operators
//

struct Unary_Plus {
    template <typename T>
    constexpr auto operator () (T const& t)
    noexcept(noexcept(+t))
    -> decltype(+t) {
        return +t;
    }
};
static constexpr Unary_Plus unary_plus{};

using Unary_Minus    = std::negate<>;     static constexpr unary_minus    = Unary_Minus{};
using Addition       = std::plus<>;       static constexpr addition       = Addition{};
using Subtraction    = std::minus<>;      static constexpr subtraction    = Subtraction{};
using Multiplication = std::multiplies<>; static constexpr multiplication = Multiplication{};
using Division       = std::divides<>;    static constexpr division       = Division{};
using Remainder      = std::modulus<>;    static constexpr remainder      = Remainder{};

struct Sum {
    template <typename... Ts>
    constexpr auto operator () (Ts const&... ts)
    noexcept(noexcept((... + ts)))
    -> decltype(... + ts) {
        return (... + ts);
    }
};
static constexpr Sum sum{};

struct Product {
    template <typename... Ts>
    constexpr auto operator () (Ts const&... ts)
    noexcept(noexcept((... * ts)))
    -> decltype(... * ts) {
        return (... * ts);
    }
};
static constexpr Product product{};

//
// Other operators
//

struct Invoke {
    template <typename T_Func, typename... T_Args>
    constexpr auto operator () (T_Func&& func, T_Args&&... args)
    noexcept(std::is_nothrow_constructible_v<T_Func, T_Args...>)
    -> std::invoke_result_t<T_Func, T_Args...> {
        return std::invoke(
            std::forward<T_Func>(func),
            std::forward<T_Args>(args)...
        );
    }
};
static constexpr Invoke invoke{};
}  // namespace ricci::xt::operators
