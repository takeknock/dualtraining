#ifndef DUAL_H_INCLUDED
#define DUAL_H_INCLUDED

#include <boost/numeric/ublas/vector.hpp>
//#include "dual_expression.h"

namespace cp {
    namespace ublas = boost::numeric::ublas;
    template <typename V>
    class Dual {
    public:
        typedef V value_type;
        //typedef typename ublas::vector<V> vector_type;
    public:
        // first, 1 dim.
        Dual(value_type value, value_type derivative)
        : _value(value), _derivative(derivative)
        {
        }

        Dual(value_type value)
        : _value(value), _derivative(1.0)
        {
        }

    public:
        value_type _value;
        //vector_type _derivative;
        value_type _derivative;
    };

    // operators as free functions
    //template <typename E1, typename E2>
    Dual<double> operator +(
        const Dual<double>& x, const Dual<double>& y)
    {
        return Dual<double>(
            x._value + y._value, x._derivative + y._derivative);
    }

    Dual<double> operator -(
        const Dual<double>& x, const Dual<double>& y)
    {
        return Dual<double>(
            x._value - y._value, x._derivative - y._derivative);
    }

    Dual<double> operator *(
        const Dual<double>& x, const Dual<double>& y)
    {
        return Dual<double>(x._value * y._value, 
            x._value * y._derivative + x._derivative * y._value);
    }

    Dual<double> operator /(
        const Dual<double>& x, const Dual<double>& y)
    {
        return Dual<double>(x._value / y._value, 
            (y._value * x._derivative - x._value * y._derivative) 
                / (y._value * y._value));
    }

    
    Dual<double> operator +(
        const Dual<double>& x, const double y)
    {
        return Dual<double>(
            x._value + y, x._derivative);
    }

    Dual<double> operator -(
        const Dual<double>& x, const double y)
    {
        return Dual<double>(
            x._value - y, x._derivative);
    }

    Dual<double> operator *(
        const Dual<double>& x, const double y)
    {
        return Dual<double>(x._value * y, x._derivative);
    }

    Dual<double> operator /(
        const Dual<double>& x, const double y)
    {
        return Dual<double>(x._value / y, 
            x._derivative / y);
    }
    

    Dual<double> operator +(
        const double x, const Dual<double>& y)
    {
        return Dual<double>(
            x + y._value, y._derivative);
    }

    Dual<double> operator -(
        const double x, const Dual<double>& y)
    {
        return Dual<double>(
            x - y._value, - y._derivative);
    }

    Dual<double> operator *(
        const double x, const Dual<double>& y)
    {
        return Dual<double>(x * y._value, 
            y._derivative);
    }

    Dual<double> operator /(
        const double x, const Dual<double>& y)
    {
        return Dual<double>(x / y._value, 
            (- x * y._derivative));
    }

	Dual<double> log(const Dual<double>& x)
	{
		return Dual<double>(std::log(x._value), x._derivative / x._value);
	}
} // namespace cp

#endif // DUAL_H_INCLUDED
