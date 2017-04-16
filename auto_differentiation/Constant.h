#pragma once
#include "ImportExportSwitch.h"

namespace ad {
    class Constant {
    public:
        DLL_API Constant(double x);
        DLL_API const double get() const;
    private:
        const double _x;
    };
} //namespace ad {
