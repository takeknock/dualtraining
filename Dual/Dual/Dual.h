#ifndef DUAL_H_INCLUDED
#define DUAL_H_INCLUDED

#include <boost/numeric/ublas/vector.hpp>
//#include "dual_expression.h"
#include "functions.h"

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
		return Dual<double>(x._value * y,
			x._derivative * y);
	}

    Dual<double> operator /(
        const Dual<double>& x, const double y)
    {
		return Dual<double>(x._value / y,
			(y * x._derivative) / (y * y));
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
			x * y._derivative + y._value);
	}

    Dual<double> operator /(
        const double x, const Dual<double>& y)
    {
		return Dual<double>(x / y._value,
			(x * y._derivative) / (y._value * y._value));
	}

	Dual<double> log(const Dual<double>& x)
	{
		return Dual<double>(std::log(x._value), x._derivative / x._value);
	}

	Dual<double> cdfOfStandardNormalDistribution(const Dual<double>& x)
	{
		boost::math::normal normalDistribution(0, 1);
		double pi = boost::math::constants::pi<double>();
		return Dual<double>(cdf(normalDistribution, x._value),
			std::exp(-x._derivative * x._derivative * 0.5) / std::sqrt(2.0 * pi));
	}


    template<typename L, typename R>
    class dual_plus {
    public:
        dual_plus(const L& lhs, const R& rhs)
        : _lhs(lhs), _rhs(rhs)
        {
        }
        Dual<double> operator()()
        {
            return lhs + rhs;
        }
    private:
        const Dual<double>& _lhs;
        const Dual<double>& _rhs;
    };

    template<typename L, typename R>
    dual_plus<L, R> operator +(
        const L& lhs, const R& rhs)
    {
        return dual_plus<L, R>(lhs, rhs);
    }

} // namespace cp

#endif // DUAL_H_INCLUDED
