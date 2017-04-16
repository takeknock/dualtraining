#include "Variable.h"

namespace ad {

    Variable::Variable(double x)
    :_x(x)
    {
    }
    
    double Variable::get()
    {
        return _x;
    }

} // namespace auto_differentiation {