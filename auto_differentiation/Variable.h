#pragma once
#include "ImportExportSwitch.h"

namespace ad {
    class Variable {
    public:
        DLL_API Variable(double x);
        DLL_API double get();
    private:
        const double _x;
    };

} //namespace auto_differentiation {
