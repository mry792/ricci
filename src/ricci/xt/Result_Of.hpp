#ifndef RICCI__XT__RESULT_OF_HPP_
#define RICCI__XT__RESULT_OF_HPP_

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

#endif  // RICCI__XT__RESULT_OF_HPP_
