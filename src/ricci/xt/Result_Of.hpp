#pragma once

namespace ricci::xt {
namespace impl_ {
template <typename T> struct Result_Of_             { using type = T;                            };
template <typename T> struct Result_Of_<T const>    { using type = typename Result_Of_<T>::type; };
template <typename T> struct Result_Of_<T volatile> { using type = typename Result_Of_<T>::type; };
template <typename T> struct Result_Of_<T&>         { using type = typename Result_Of_<T>::type; };
template <typename T> struct Result_Of_<T&&>        { using type = typename Result_Of_<T>::type; };
}  // namespace impl_

template <typename T>
using Result_Of = typename impl_::Result_Of_<T>::type;
}  // namespace ricci::xt
