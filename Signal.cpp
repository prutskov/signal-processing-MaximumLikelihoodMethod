#include "stdafx.h"
#include "Signal.h"
#include <random>
#include <ctime>

template Signal<float>;
template Signal<double>;

template<typename fptype>
Signal<fptype>::Signal(size_t nBits, fptype A, fptype f0, fptype bt, fptype fd)
	: _A(A), _f0(f0), _bt(bt), _fd(fd)
{
	_dataBits.resize(nBits);

	std::mt19937 generator(static_cast<unsigned int>(time(0)));
	std::uniform_int_distribution<int> distribution(0, 1);
	for (size_t i = 0; i < nBits; ++i)
	{
		_dataBits[i] = static_cast<unsigned char>(distribution(generator));
	}

	modulateSignal();
}

template<typename fptype>
std::vector<unsigned char> * Signal<fptype>::getData()
{
	return &_dataBits;
}

template<typename fptype>
std::vector<PointF>* Signal<fptype>::getSignalPoints()
{
	return &_signalModulated;
}

template<typename fptype>
Signal<fptype>::~Signal()
{
	_dataBits.clear();
}

template<typename fptype>
void Signal<fptype>::modulateSignal()
{
	const fptype Td = static_cast<fptype>(1) / _fd;
	const fptype TmodPerBit = static_cast<fptype>(1) / _bt;
	const fptype timeOfSignal = TmodPerBit * _dataBits.size();


	auto A = [&](const unsigned char bit)
	{
		if (bit == 1)
			return _A;
		else
			return _A / static_cast<fptype>(2);
	};

	_dataModulated.clear();
	_signalModulated.clear();
	size_t bitIdx = 0;
	fptype curBitTime = 0;
	for (fptype time = 0; time < timeOfSignal; time+=Td)
	{
		if (curBitTime < TmodPerBit)
		{
			curBitTime += Td;
		}
		else
		{
			++bitIdx;
			curBitTime = 0.0;
		}

		_dataModulated.emplace_back(A(_dataBits[bitIdx])*sin(2.*M_PI*_f0*time));

		PointF point(time, *_dataModulated.end());
		_signalModulated.emplace_back(point);
	}
}
