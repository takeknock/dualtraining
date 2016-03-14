#pragma once
#include "IModel.h"

template <typename C, typename T>
class IContract<C, T> {
	typedef T value_type;
	static value_type operator()()
	{
		return static_cast<C&>(*this);
	}
	value_type calculatePrice(const IModel<C&> model)
	{
		return static_cast<C&>(*this)->calculatePrice(model);
	}
};
