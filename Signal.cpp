#include "stdafx.h"
#include "Signal.h"
#include <random>
#include <ctime>

template Signal<float>;

template<typename fptype>
Signal<fptype>::Signal(const size_t size)
{
	_data.resize(size);

	std::mt19937 generator(time(0));
	std::uniform_real_distribution<fptype> distribution(0, 1);
	for (size_t i = 0; i < size; ++i)
	{
		_data[i] = distribution(generator);
	}
}

template<typename fptype>
std::vector<fptype> * Signal<fptype>::getData()
{
	return &_data;
}

template<typename fptype>
Signal<fptype>::~Signal()
{
	_data.clear();
}
