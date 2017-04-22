#pragma once
#include "ImportExportSwitch.h"

namespace ad {
    struct add_op {};
    struct sub_op {};
    struct mul_op {};
    struct div_op {};


    template<typename OP, typename E1, typename E2>
    class binary_expression {
    public:
        explicit binary_expression<OP, E1, E2>(const E1& e1, const E2& e2)
        :_e1(e1),_e2(e2)
        {}

        const E1& e1() const
        {
            return _e1;
        }
        const E2& e2() const
        {
            return _e2;
        }

    private:
        const E1 _e1;
        const E2 _e2;
    };
}// namespace ad {
