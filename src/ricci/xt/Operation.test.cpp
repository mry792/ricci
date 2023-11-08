
#include "ricci/xt/Operation.hpp"

#include <functional>

#include "ricci/xt/Result_Of.hpp"


int func (double, double) { return 0; }

using ricci::xt::Operation;
using ricci::xt::Result_Of;

static_assert(
    std::is_same_v<
        Result_Of<
            Operation<
                std::plus<>{},
                double,
                float
            >
        >,
        double
    >
);

static_assert(
    std::is_same_v<
        Result_Of<
            Operation<
                &func,
                Operation<
                    std::plus<>{},
                    double,
                    float
                >,
                double
            >
        >,
        int
    >
);
