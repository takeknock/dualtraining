#pragma once

#include "binary_traits.h"

namespace ad
{
    template<typename E, typename D>
    class dual_number {
    public:
        typedef dual_number<E, D> this_type;

        inline dual_number(const E e, const D d = D(0))
        :_e(e), _d(d)
        {
        }

        // copy constructor
        inline dual_number(const this_type& rhs) 
        {
            _e = rhs.e();
            _d = rhs.d();
        }

        // desctructor
        virtual ~dual_number()
        {

        }

        // operators for dual_number v.s. dual_number
        inline this_type& operator+=(const this_type& rhs)
        {
            _e += rhs.e();
            _d += rhs.d();
            return this*;
        }

        inline this_type& operator-=(const this_type& rhs)
        {
            _e -= rhs.e();
            _d -= rhs.d();
            return this*;
        }

        inline this_type& operator*=(const this_type& rhs)
        {
            _e *= rhs.e();
            _d = _d * rhs.e() + _e * rhs.d();
            return this*;
        }

        inline this_type& operator/=(const this_type& rhs)
        {
            _e /= rhs.e();
            _d = (_d * rhs.e() - _e * rhs.d()) / (rhs.e() * rhs.e());
            return this*;
        }

        inline this_type& operator +(const this_type& rhs)
        {
            return this_type(*this) += rhs;
        }

        inline this_type& operator -(const this_type& rhs)
        {
            return this_type(*this) -= rhs;
        }

        inline this_type& operator *(const this_type& rhs)
        {
            return this_type(*this) *= rhs;
        }

        inline this_type& operator /(const this_type& rhs)
        {
            return this_type(*this) /= rhs;
        }

        // unitary operators for any rhs types
        template<typename E, typename D, typename ER, typename DR>
        inline dual_number<binary_traits<E, ER>::value_type, binary_traits<D, DR>::value_type>
            operator+=(const dual_number<ER, DR>& rhs)
        {
            _e += rhs.e();
            _d += rhs.d();
            return this*;
        }

        template<typename E, typename D, typename ER, typename DR>
        inline dual_number<binary_traits<E, ER>::value_type, binary_traits<D, DR>::value_type>&
            operator-=(const dual_number<ER, DR>& rhs)
        {
            _e -= rhs.e();
            _d -= rhs.d();
            return this*;
        }

        template<typename E, typename D, typename ER, typename DR>
        inline dual_number<binary_traits<E, ER>::value_type, binary_traits<D, DR>::value_type>&
            operator*=(const dual_number<ER, DR>& rhs)
        {
            _e *= rhs.e();
            _d = _d * rhs.e() + _e * rhs.d();
            return this*;
        }

        template<typename E, typename D, typename ER, typename DR>
        inline dual_number<binary_traits<E, ER>::value_type, binary_traits<D, DR>::value_type>&
            operator/=(const dual_number<ER, DR>& rhs)
        {
            _e /= rhs.e();
            _d = (_d * rhs.e() - _e * rhs.d()) / (rhs.e() * rhs.e());
            return this*;
        }

        template<typename E, typename D, typename ER, typename DR>
        inline dual_number<binary_traits<E, ER>::value_type, binary_traits<D, DR>::value_type>&
            operator +(const dual_number<ER, DR>& rhs)
        {
            return this_type(*this) += rhs;
        }

        template<typename E, typename D, typename ER, typename DR>
        inline dual_number<binary_traits<E, ER>::value_type, binary_traits<D, DR>::value_type>&
            operator -(const dual_number<ER, DR>& rhs)
        {
            return this_type(*this) -= rhs;
        }

        template<typename E, typename D, typename ER, typename DR>
        inline dual_number<binary_traits<E, ER>::value_type, binary_traits<D, DR>::value_type>&
            operator *(const dual_number<ER, DR>& rhs)
        {
            return this_type(*this) *= rhs;
        }

        template<typename E, typename D, typename ER, typename DR>
        inline dual_number<binary_traits<E, ER>::value_type, binary_traits<D, DR>::value_type>&
            operator /(const dual_number<ER, DR>& rhs)
        {
            return this_type(*this) /= rhs;
        }

        const E& e() const 
        {
            return _e;
        }
        const D& d() const 
        {
            return _d;
        }

    private:
        E _e;
        D _d;

    };


    // binary operators for any rhs types
    template<typename E, typename D, typename ER, typename DR>
    inline dual_number<binary_traits<E, ER>::value_type, binary_traits<D, DR>::value_type>
        operator+(const dual_number<E, D>& lhs, const dual_number<ER, DR>& rhs)
    {
        binary_traits<E, ER>::value_type e = lhs.e() + rhs.e();
        binary_traits<D, DR>::value_type d = lhs.d() + rhs.d();
        return dual_number<binary_traits<E, ER>::value_type, binary_traits<D, DR>::value_type>(e, d);
    }

    template<typename E, typename D, typename ER, typename DR>
    inline dual_number<binary_traits<E, ER>::value_type, binary_traits<D, DR>::value_type>&
        operator-(const dual_number<E, D>& lhs, const dual_number<ER, DR>& rhs)
    {
        binary_traits<E, ER>::value_type e = lhs.e() - rhs.e();
        binary_traits<D, DR>::value_type d = lhs.d() - rhs.d();
        return dual_number<binary_traits<E, ER>::value_type, binary_traits<D, DR>::value_type>(e, d);
    }

    template<typename E, typename D, typename ER, typename DR>
    inline dual_number<binary_traits<E, ER>::value_type, binary_traits<D, DR>::value_type>&
        operator*(const dual_number<E, D>& lhs, const dual_number<ER, DR>& rhs)
    {
        binary_traits<E, ER>::value_type e = lhs.e() * rhs.e();
        binary_traits<D, DR>::value_type d = lhs.d() * rhs.e() + lhs.e() * rhs.d();
        return dual_number<binary_traits<E, ER>::value_type, binary_traits<D, DR>::value_type>(e, d);
    }

    template<typename E, typename D, typename ER, typename DR>
    inline dual_number<binary_traits<E, ER>::value_type, binary_traits<D, DR>::value_type>&
        operator/(const dual_number<E, D>& lhs, const dual_number<ER, DR>& rhs)
    {
        binary_traits<E, ER>::value_type e = lhs.e() / rhs.e();
        binary_traits<D, DR>::value_type d = (lhs.d() * rhs.e() - lhs.e() * rhs.d()) / (rhs.e() * rhs.e());
        return dual_number<binary_traits<E, ER>::value_type, binary_traits<D, DR>::value_type>(e, d);
    }
}