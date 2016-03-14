#pragma once

template <typename T>
class IModel<T> {
	typedef T value_type;
	static value_type operator()(const T& x)
	{
		return static_cast<T>(*this);
	}
};
