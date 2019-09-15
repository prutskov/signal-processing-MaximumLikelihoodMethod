#include "stdafx.h"
#include "Signal.h"
#include <random>
#include <ctime>

template Signal<float>;
template Signal<double>;

template<typename fptype>
Signal<fptype>::Signal(SignalParameter<fptype> params)
	: _par(params)
{
	_dataBits.resize(_par._nBits);

	std::mt19937 generator(static_cast<unsigned int>(time(0)));
	std::uniform_int_distribution<int> distribution(0, 1);
	for (size_t i = 0; i < _par._nBits; ++i)
	{
		_dataBits[i] = static_cast<uint8_t>(distribution(generator));
	}

	modulateSignal();
}

template<typename fptype>
Signal<fptype>::Signal(Signal<fptype> *signal, size_t tau)
{
	_par = *(signal->getParameters());
	_par._nBits *= 2;
	_dataBits.resize(_par._nBits);
	auto bits = signal->getData();
	
	std::mt19937 generator(static_cast<unsigned int>(time(0)));
	std::uniform_int_distribution<int> distribution(0, 1);
	for (size_t i = 0; i < _par._nBits; ++i)
	{
		_dataBits[i] = static_cast<uint8_t>(distribution(generator));
	}

	const size_t sizeRef = signal->_par._nBits;

	for (size_t i = 0; i < sizeRef; ++i)
	{
		_dataBits[tau + i] = bits[i];
	}

	modulateSignal();
}

template<typename fptype>
std::vector<uint8_t> Signal<fptype>::getData()
{
	return _dataBits;
}

template<typename fptype>
SignalParameter<fptype>* Signal<fptype>::getParameters()
{
	return &_par;
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
	_dataModulated.clear();
	_signalModulated.clear();
}

template<typename fptype>
void Signal<fptype>::modulateSignal()
{
	const fptype Td = static_cast<fptype>(1) / _par._fd;
	const fptype TmodPerBit = static_cast<fptype>(1) / _par._bt;
	const fptype timeOfSignal = TmodPerBit * _dataBits.size();


	auto A = [&](const uint8_t bit)
	{
		if (bit == 1)
			return _par._A;
		else
			return _par._A / static_cast<fptype>(2);
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

		_dataModulated.emplace_back(A(_dataBits[bitIdx])*sin(2.*M_PI*_par._f0*time));

		PointF point(time, _dataModulated.back());
		_signalModulated.emplace_back(point);
	}

	generateNoise();
}

template<typename fptype>
void Signal<fptype>::generateNoise()
{
	const size_t size = _dataModulated.size();
	std::vector<fptype> noise(size, 0);

	for (size_t i = 0; i < size; ++i)
	{
		fptype M, ksi;
		M = rand() % 9 + 12;
		ksi = 0;
		for (int k = 1; k <= M; k++)
		{
			ksi += (fptype)((rand() % 21 - 10) / 10.);
		}
		noise[i] = ksi / M;
	}
	
	fptype alfa = sqrt(exp(log((fptype)10.0)*_par._SNR/10.));

	for (size_t i = 0; i < size; ++i)
	{
		_dataModulated[i] += alfa * noise[i];
		_signalModulated[i].Y = _dataModulated[i];
	}
}
