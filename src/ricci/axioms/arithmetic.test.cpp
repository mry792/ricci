
#ifndef RICCI_MACRO_DEBUGGING
#include "ricci/axioms/arithmetic.hpp"

#include "ricci/axioms/associativity.hpp"
#include "ricci/axioms/closure.hpp"
#include "ricci/axioms/commutativity.hpp"
#include "ricci/axioms/distributivity.hpp"
#include "ricci/axioms/identity.hpp"
#include "ricci/axioms/inverse.hpp"
#include "ricci/core/operators.hpp"
#endif

#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>

#include "ricci/pp/macro_debugging.hpp"


#define RICCI_MAKE_BINARY_PREDICATE_ASSERT(r, prod)            \
static_assert(                                                 \
    BOOST_PP_SEQ_ELEM(0, prod)<                                \
        BOOST_PP_SEQ_ELEM(1, prod),                            \
        BOOST_PP_SEQ_ELEM(2, prod) BOOST_PP_SEQ_ELEM(3, prod), \
        BOOST_PP_SEQ_ELEM(4, prod) BOOST_PP_SEQ_ELEM(5, prod)  \
    >                                                          \
); __NL__

#define RICCI_MAKE_UNARY_PREDICATE_ASSERT(r, prod)            \
static_assert(                                                \
    BOOST_PP_SEQ_ELEM(0, prod)<                               \
        BOOST_PP_SEQ_ELEM(1, prod),                           \
        BOOST_PP_SEQ_ELEM(2, prod) BOOST_PP_SEQ_ELEM(3, prod) \
    >                                                         \
); __NL__

#define RICCI_MAKE_TRINARY_PREDICATE_ASSERT(r, prod)            \
static_assert(                                                  \
    BOOST_PP_SEQ_ELEM(0, prod)<                                 \
        BOOST_PP_SEQ_ELEM(1, prod), BOOST_PP_SEQ_ELEM(2, prod), \
        BOOST_PP_SEQ_ELEM(3, prod) BOOST_PP_SEQ_ELEM(4, prod),  \
        BOOST_PP_SEQ_ELEM(5, prod) BOOST_PP_SEQ_ELEM(6, prod),  \
        BOOST_PP_SEQ_ELEM(7, prod) BOOST_PP_SEQ_ELEM(8, prod)   \
    >                                                           \
); __NL__

namespace {
namespace operators = ricci::core::operators;
using ricci::axioms::is_associative;
using ricci::axioms::is_closed;
using ricci::axioms::is_commutative;
using ricci::axioms::is_distributive;
using ricci::axioms::is_left_distributive;
using ricci::axioms::is_right_distributive;
using ricci::axioms::has_identity;
using ricci::axioms::has_inverse;

#define BINARY_PREDICATES (is_associative)(is_closed)(is_commutative)(has_identity)
#define ARITHMETIC_TYPES (int)(short)(long)(double)(float)
#define QUALIFIERS ()(&)(&&)( const)( const&)

// All binary predicates hold for addition and multiplication.
BOOST_PP_SEQ_FOR_EACH_PRODUCT(
    RICCI_MAKE_BINARY_PREDICATE_ASSERT,
    (BINARY_PREDICATES)
    ((operators::add)(operators::multiply))
    (ARITHMETIC_TYPES)(QUALIFIERS)
    (ARITHMETIC_TYPES)(QUALIFIERS)
)

// Some binary predicates also hold for subtraction and division.
BOOST_PP_SEQ_FOR_EACH_PRODUCT(
    RICCI_MAKE_BINARY_PREDICATE_ASSERT,
    ((is_closed)(has_identity))
    ((operators::subtract)(operators::divide))
    (ARITHMETIC_TYPES)(QUALIFIERS)
    (ARITHMETIC_TYPES)(QUALIFIERS)
)

// All unary predicates hold for addition.
BOOST_PP_SEQ_FOR_EACH_PRODUCT(
    RICCI_MAKE_UNARY_PREDICATE_ASSERT,
    ((has_inverse))
    ((operators::add))
    (ARITHMETIC_TYPES)(QUALIFIERS)
)

// Some unary predicates hold for multiplication.
BOOST_PP_SEQ_FOR_EACH_PRODUCT(
    RICCI_MAKE_UNARY_PREDICATE_ASSERT,
    ((has_inverse))
    ((operators::multiply))
    ((float)(double))(QUALIFIERS)
)

// Integral types do not have a multiplicative inverse.
BOOST_PP_SEQ_FOR_EACH_PRODUCT(
    RICCI_MAKE_UNARY_PREDICATE_ASSERT,
    ((not has_inverse))
    ((operators::multiply))
    ((int)(short)(long))(QUALIFIERS)
)

// Subtraction with unsigned numbers is not closed.
BOOST_PP_SEQ_FOR_EACH_PRODUCT(
    RICCI_MAKE_BINARY_PREDICATE_ASSERT,
    ((not is_closed))
    ((operators::subtract))
    ((unsigned)(unsigned short)(unsigned long))(QUALIFIERS)
    (ARITHMETIC_TYPES)(QUALIFIERS)
)
BOOST_PP_SEQ_FOR_EACH_PRODUCT(
    RICCI_MAKE_BINARY_PREDICATE_ASSERT,
    ((not is_closed))
    ((operators::subtract))
    (ARITHMETIC_TYPES)(QUALIFIERS)
    ((unsigned)(unsigned short)(unsigned long))(QUALIFIERS)
)

// Use this to cut down on the number of tests.
#define SOME_ARITHMETIC_TYPES (int)(double)

// Multiplication is fully distributive over addition and subtraction.
BOOST_PP_SEQ_FOR_EACH_PRODUCT(
    RICCI_MAKE_TRINARY_PREDICATE_ASSERT,
    ((is_distributive)(is_left_distributive)(is_right_distributive))
    ((operators::multiply))
    ((operators::add)(operators::subtract))
    (SOME_ARITHMETIC_TYPES)(QUALIFIERS)
    (SOME_ARITHMETIC_TYPES)(QUALIFIERS)
    (SOME_ARITHMETIC_TYPES)(QUALIFIERS)
)

// Division is only right-distributive over addition and subtraction but only if
// every term evaluates to a floating point number.
BOOST_PP_SEQ_FOR_EACH_PRODUCT(
    RICCI_MAKE_TRINARY_PREDICATE_ASSERT,
    ((not is_distributive)(not is_left_distributive)(is_right_distributive))
    ((operators::divide))
    ((operators::add)(operators::subtract))
    ((double))(QUALIFIERS)
    (SOME_ARITHMETIC_TYPES)(QUALIFIERS)
    (SOME_ARITHMETIC_TYPES)(QUALIFIERS)
)
BOOST_PP_SEQ_FOR_EACH_PRODUCT(
    RICCI_MAKE_TRINARY_PREDICATE_ASSERT,
    ((not is_distributive)(not is_left_distributive)(is_right_distributive))
    ((operators::divide))
    ((operators::add)(operators::subtract))
    (SOME_ARITHMETIC_TYPES)(QUALIFIERS)
    ((double))(QUALIFIERS)
    ((double))(QUALIFIERS)
)
BOOST_PP_SEQ_FOR_EACH_PRODUCT(
    RICCI_MAKE_TRINARY_PREDICATE_ASSERT,
    ((not is_distributive)(not is_left_distributive)(not is_right_distributive))
    ((operators::divide))
    ((operators::add)(operators::subtract))
    ((int))(QUALIFIERS)
    ((int))(QUALIFIERS)
    ((double))(QUALIFIERS)
)
BOOST_PP_SEQ_FOR_EACH_PRODUCT(
    RICCI_MAKE_TRINARY_PREDICATE_ASSERT,
    ((not is_distributive)(not is_left_distributive)(not is_right_distributive))
    ((operators::divide))
    ((operators::add)(operators::subtract))
    ((int))(QUALIFIERS)
    ((double))(QUALIFIERS)
    ((int))(QUALIFIERS)
)

#undef RICCI_MAKE_BINARY_PREDICATE_ASSERT
#undef RICCI_MAKE_UNARY_PREDICATE_ASSERT
#undef RICCI_MAKE_TRINARY_PREDICATE_ASSERT
#undef BINARY_PREDICATES
#undef OPERATIONS
#undef ARITHMETIC_TYPES
#undef SOME_ARITHMETIC_TYPES
#undef QUALIFIERS
}  // namespace
