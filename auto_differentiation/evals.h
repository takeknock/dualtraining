#pragma once
#include "binary_expression.h";
#include "Variable.h";
#include "Constant.h";


namespace ad {
    auto eval(const ad::Variable& e)
    {
        return e.get();
    }

    auto eval(const double e)
    {
        return e;
    }

    template<typename E1, typename E2>
    auto eval(const binary_expression<add_op, E1, E2>& e)
    {
        return eval(e.e1()) + eval(e.e2());
    }

    template<typename E1, typename E2>
    auto eval(const binary_expression<sub_op, E1, E2>& e)
    {
        return eval(e.e1()) - eval(e.e2());
    }

    template<typename E1, typename E2>
    auto eval(const binary_expression<mul_op, E1, E2>& e)
    {
        return eval(e.e1()) * eval(e.e2());
    }

    template<typename E1, typename E2>
    auto eval(const binary_expression<div_op, E1, E2>& e)
    {
        return eval(e.e1()) / eval(e.e2());
    }

} // namespace ad
