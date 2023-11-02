
#include "ricci/pp/macro_debugging.hpp"

#ifndef RICCI_MACRO_DEBUGGING
#include "ricci/axioms/associativity.hpp"
#include <functional>
#endif

#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>


#define RICCI_MAKE_IS_ASSOCIATIVE_ASSERT(r, prod) \
static_assert(                                    \
    is_associative<BOOST_PP_SEQ_ELEM(0, prod),    \
    BOOST_PP_SEQ_ELEM(1, prod),                   \
    BOOST_PP_SEQ_ELEM(2, prod)                    \
>); __NL__ \


#define OPERATIONS (std::plus<>{})(std::multiplies<>{})
#define ARITHMETIC_TYPES (int)(short)(long)(double)(float)

using ricci::axioms::is_associative;

BOOST_PP_SEQ_FOR_EACH_PRODUCT(
    RICCI_MAKE_IS_ASSOCIATIVE_ASSERT,
    (OPERATIONS)(ARITHMETIC_TYPES)(ARITHMETIC_TYPES)
)

#undef OPERATIONS
#undef ARITHMETIC_TYPES
