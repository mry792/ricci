
#include "ricci/xt/Placeholder.hpp"

#include <concepts>
#include <sstream>
#include <utility>

#include <boost/hana/pair.hpp>
#include <boost/hana/second.hpp>
#include <boost/yap/expression.hpp>
#include <boost/yap/print.hpp>
#include <catch2/catch_test_macros.hpp>

#include "ricci/xt/Result_Of.hpp"

RICCI_MAKE_PLACEHOLDER_TAG(Testing);

namespace {
using ricci::xt::Placeholder;
using ricci::xt::Result_Of;

static_assert(std::same_as<Result_Of<Placeholder<short, Testing_Tag>>, short>);
}  // namespace

TEST_CASE ("ricci::xt::Placeholder - operator <<") {
    using ricci::xt::Placeholder;

    using boost::yap::make_terminal;
    using boost::yap::print;

    std::stringstream buffer;

    print(buffer, make_terminal(Placeholder<int, Testing_Tag>{}));
    CHECK(buffer.str() ==
        "term<ricci::xt::Placeholder<int, Testing_Tag>>[=Testing]\n");
}

TEST_CASE ("ricci::xt::Placeholder - operator =") {
    using ricci::xt::Placeholder;

    using boost::hana::pair;
    using boost::hana::second;

    using Plh = Placeholder<double, Testing_Tag>;
    Plh placeholder;

    SECTION ("literal") {
        auto substitution = (placeholder = 7);
        static_assert(std::same_as<decltype(substitution), pair<Plh, int>>);
        CHECK(second(substitution) == 7);
    }

    SECTION ("variable") {
        float value = 2.3;
        auto substitution = (placeholder = value);
        static_assert(std::same_as<decltype(substitution), pair<Plh, float&>>);
        CHECK(&second(substitution) == &value);
    }

    SECTION ("moved variable") {
        long value = -88;
        auto substitution = (placeholder = std::move(value));
        static_assert(std::same_as<decltype(substitution), pair<Plh, long>>);
        CHECK(second(substitution) == -88);
    }
}
