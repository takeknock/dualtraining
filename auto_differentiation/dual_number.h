#pragma once

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
}