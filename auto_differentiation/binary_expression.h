#pragma once
#include "ImportExportSwitch.h"

namespace ad {
    template<typename OP, typename E1, typename E2>
    class binary_expression {
    public:
        DLL_API binary_expression(E1 &e1, E2 &e2)
        :_e1(e1),_e2(e2)
        {}

        DLL_API E1& e1()
            return _e1;
        DLL_API E2& e2()
            return _e2;

    private:
        const E1& _e1;
        const E2& _e2;
    };
}// namespace ad {
