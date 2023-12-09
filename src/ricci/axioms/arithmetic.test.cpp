
#ifndef RICCI_MACRO_DEBUGGING
#include "ricci/axioms/arithmetic.hpp"

#include "ricci/axioms/associativity.hpp"
#include "ricci/axioms/commutativity.hpp"
#include "ricci/axioms/identity.hpp"
#include "ricci/core/operators.hpp"
#endif

#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>

#include "ricci/pp/macro_debugging.hpp"


#define RICCI_MAKE_PREDICATE_ASSERT(r, prod)                   \
static_assert (                                                \
    BOOST_PP_SEQ_ELEM(0, prod)<                                \
        BOOST_PP_SEQ_ELEM(1, prod),                            \
        BOOST_PP_SEQ_ELEM(2, prod) BOOST_PP_SEQ_ELEM(3, prod), \
        BOOST_PP_SEQ_ELEM(4, prod) BOOST_PP_SEQ_ELEM(5, prod)  \
    >                                                          \
); __NL__

namespace {
namespace operators = ricci::core::operators;
using ricci::axioms::is_associative;
using ricci::axioms::is_commutative;
using ricci::axioms::has_identity;

#define PREDICATES (is_associative)(is_commutative)(has_identity)
#define OPERATIONS (operators::add)(operators::multiply)
#define ARITHMETIC_TYPES (int)(short)(long)(double)(float)
#define QUALIFIERS ()(&)(&&)( const)( const&)

BOOST_PP_SEQ_FOR_EACH_PRODUCT(
    RICCI_MAKE_PREDICATE_ASSERT,
    (PREDICATES)
    (OPERATIONS)
    (ARITHMETIC_TYPES)(QUALIFIERS)
    (ARITHMETIC_TYPES)(QUALIFIERS)
)

#undef RICCI_MAKE_PREDICATE_ASSERT
#undef PREDICATES
#undef OPERATIONS
#undef ARITHMETIC_TYPES
#undef QUALIFIERS
}  // namespace
