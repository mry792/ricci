#ifndef RICCI__CONCEPTS__STD_EXT_HPP_
#define RICCI__CONCEPTS__STD_EXT_HPP_

#include <type_traits>

namespace ricci::concepts {
template <typename T>
concept Arithmetic = std::is_arithmetic_v<std::remove_cvref_t<T>>;
}  // namespace ricci::concepts

#endif  // RICCI__CONCEPTS__STD_EXT_HPP_
