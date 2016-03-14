#pragma once
#include "IContract.h"

template <typename M, typename T>
class Cap<M, T> : public IContract<Cap> {
	typedef T value_type;
	Cap(const double strike, const M& model, const double maturity)
	{
	};
};