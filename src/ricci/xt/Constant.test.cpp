
#include "ricci/xt/Constant.hpp"

#include <concepts>
#include <sstream>

#include <boost/yap/expression.hpp>
#include <boost/yap/print.hpp>
#include <catch2/catch_test_macros.hpp>

#include "ricci/xt/Result_Of.hpp"

namespace {
struct Tag {};
inline constexpr Tag tag_value{};
constexpr Tag make_tag () { return {}; }

std::ostream& operator << (std::ostream& out, Tag) {
    return out << "(Tag)";
}
}  // namespace

TEST_CASE ("ricci::xt::Constant - operator <<") {
    using ricci::xt::Constant;

    using boost::yap::make_terminal;
    using boost::yap::print;

    std::stringstream buffer;

    SECTION ("int") {
        print(buffer, make_terminal(Constant<-7>{}));
        CHECK(buffer.str() == "term<ricci::xt::Constant<-7>>[=-7]\n");
    }

    SECTION ("Tag") {
        print(buffer, make_terminal(Constant<Tag{}>{}));
        CHECK(buffer.str() == "term<ricci::xt::Constant<(anonymous namespace)::Tag{}>>[=(Tag)]\n");
    }
}

namespace TEST_CASE_Result_Of {
    using ricci::xt::Constant;
    using ricci::xt::Result_Of;

    static_assert(std::same_as<Result_Of<Constant<-7>>, int>);
    static_assert(std::same_as<Result_Of<Constant<2.3>>, double>);

    static_assert(std::same_as<Result_Of<Constant<Tag{}>>, Tag const>);
    static_assert(std::same_as<Result_Of<Constant<tag_value>>, Tag const>);
    static_assert(std::same_as<Result_Of<Constant<make_tag()>>, Tag const>);
}  // namespace TEST_CASE_Result_Of
