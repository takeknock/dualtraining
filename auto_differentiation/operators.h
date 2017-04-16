#pragma once
#include "binary_expression.h";
#include "ImportExportSwitch.h";


namespace ad {
    

    template<typename E1, typename E2>
    binary_expression<add_op, E1, E2> operator +(const E1& e1, const E2& e2)
    {
        return binary_expression<add_op, E1, E2>(e1, e2);
    }

    template<typename E1, typename E2>
    binary_expression<sub_op, E1, E2> operator -(const E1& e1, const E2& e2)
    {
        return binary_expression<sub_op, E1, E2>(e1, e2);
    }

    template<typename E1, typename E2>
    binary_expression<mul_op, E1, E2> operator *(const E1& e1, const E2& e2)
    {
        return binary_expression<mul_op, E1, E2>(e1, e2);
    }

    template<typename E1, typename E2>
    binary_expression<div_op, E1, E2> operator /(const E1& e1, const E2& e2)
    {
        return binary_expression<div_op, E1, E2>(e1, e2);
    }

}// namespace ad

