#pragma once

#include "ricci/mp/Member.hpp"

namespace ricci::xt {
template <typename T_Placeholder, typename T_Expression>
struct Substitution : ricci::mp::Member<T_Expression> {
  private:
    using Repl_Member = ricci::mp::Member<T_Expression>;

  public:
    using Target = T_Placeholder;
    using Replacement = T_Expression;

    constexpr Replacement&       replacement () &      { return static_cast<Repl_Member&      >(*this).get_(); }
    constexpr Replacement const& replacement () const& { return static_cast<Repl_Member const&>(*this).get_(); }
    constexpr Replacement&&      replacement () &&     { return static_cast<Repl_Member&&     >(*this).get_(); }
};
}  // namespace ricci::xt
