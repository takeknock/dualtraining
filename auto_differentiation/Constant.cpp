#include "Constant.h"

namespace ad {
    Constant::Constant(double x)
    :_x(x)
    {}
    const double Constant::get() const
    {
        return _x;
    }
}//namespace ad {
