#pragma once

#include "binary_expression.h"
#include "Constant.h"
#include "Variable.h"

namespace ad {
    double diff(const Variable& e)
    {
        return 1.0;
    }

    double diff(const Constant& e)
    {
        return 0.0;
    }

    double diff(const double e)
    {
        return 0.0;
    }

    template<typename E1, typename E2>
    auto diff(const binary_expression<add_op, E1, E2>& e)
    {
        return diff(e.e1()) + diff(e.e2());
    }

    template<typename E1, typename E2>
    auto diff(const binary_expression<sub_op, E1, E2>& e)
    {
        return diff(e.e1()) - diff(e.e2());
    }

    template<typename E1, typename E2>
    auto diff(const binary_expression<mul_op, E1, E2>& e)
    {
        return diff(e.e1()) * eval(e.e2()) + diff(e.e2()) * eval(e.e1());
    }

} // namespace ad {
