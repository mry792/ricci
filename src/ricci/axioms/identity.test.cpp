
#include "ricci/pp/macro_debugging.hpp"

#ifndef RICCI_MACRO_DEBUGGING
#include "ricci/axioms/identity.hpp"

#include "ricci/xt/operators.hpp"
#endif

#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>


#define RICCI_MAKE_HAS_IDENTITY_ASSERT(r, prod)                 \
static_assert(                                                  \
    has_identity<                                               \
        BOOST_PP_SEQ_ELEM(0, prod),                             \
        BOOST_PP_SEQ_ELEM(1, prod) BOOST_PP_SEQ_ELEM(2, prod),  \
        BOOST_PP_SEQ_ELEM(3, prod) BOOST_PP_SEQ_ELEM(4, prod)   \
    >                                                           \
); __NL__

namespace operators = ricci::xt::operators;
using ricci::axioms::has_identity;

#define OPERATIONS (operators::add)(operators::multiply)
#define ARITHMETIC_TYPES (int)(short)(long)(double)(float)
#define QUALIFIERS ()( const)( volatile)( const volatile)

BOOST_PP_SEQ_FOR_EACH_PRODUCT(
    RICCI_MAKE_HAS_IDENTITY_ASSERT,
    (OPERATIONS)
    (ARITHMETIC_TYPES)(QUALIFIERS)
    (ARITHMETIC_TYPES)(QUALIFIERS)
)

#undef OPERATIONS
#undef ARITHMETIC_TYPES
#undef QUALIFIERS