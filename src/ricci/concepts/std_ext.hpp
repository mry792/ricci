#pragma once

#include <type_traits>

namespace ricci::concepts {
template <typename T>
concept Arithmetic = std::is_arithmetic_v<std::remove_cvref_t<T>>;
}  // namespace ricci::concepts
