#pragma once

namespace ricci::xt {
namespace impl_ {
template <typename T>
struct Result_Of_ {
    using type = T;
};
}  // namespace impl_

template <typename T>
using Result_Of = typename impl_::Result_Of_<T>::type;
}  // namespace ricci::xt
