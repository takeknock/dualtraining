#pragma once
#include "binary_expression.h";
#include "Constant.h";
#include "Variable.h";

namespace ad {
    auto diff(Variable& e)
    {
        return 1;
    }

    auto diff(Constant& e)
    {
        return 0;
    }

    template<typename E1, typename E2>
    auto diff(binary_expression<add_op, E1, E2>& e)
    {
        return diff(e.e1()) + diff(e.e2());
    }
} // namespace ad {
