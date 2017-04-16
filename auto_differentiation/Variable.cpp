#include "Variable.h"

namespace ad {

    Variable::Variable(double x)
    :_x(x)
    {
    }
    
    const double Variable::get() const
    {
        return _x;
    }

} // namespace auto_differentiation {