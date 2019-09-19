#include "stdafx.h"
#include "Signal.h"
#include <random>
#include <algorithm>
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
Signal<fptype>::Signal(Signal<fptype> *signal, SignalParameter<fptype> params, size_t tau)
{
	_par = *(signal->getParameters());
	_par._nBits *= 2;
	_par._SNR = params._SNR;
	_tau.nReference = tau;

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
std::vector<PointF>* Signal<fptype>::getCorrelationPoints()
{
	return &_correlationPoints;
}


template<typename fptype>
fptype Signal<fptype>::getCorrelation(Signal<fptype>* signal2)
{
	fptype correlation = 0.0;
	auto signalModulated2 = signal2->getSignalPoints();

	const size_t size = signalModulated2->size();
	const size_t maxShift = this->_signalModulated.size() - size;

	vector<fptype> corr(maxShift + 1, 0.0);
	_correlationPoints.clear();
	_correlationPoints.resize(maxShift + 1);
	for (size_t shift = 0; shift <= maxShift; ++shift)
	{
		for (size_t idx = 0; idx < size; ++idx)
		{
			corr[shift] += signalModulated2[0][idx].Y * _signalModulated[idx + shift].Y;
		}

		corr[shift] < 0 ? corr[shift] = 0.0 : corr[shift] /= size;
		_correlationPoints[shift].Y = corr[shift];
		_correlationPoints[shift].X = shift;
	}

	auto maxVal = std::max_element(corr.begin(), corr.end());
	size_t maxIdx = std::distance(corr.begin(), maxVal);
	_tau.val = _signalModulated[maxIdx].X;

	return *maxVal;
}

template<typename fptype>
fptype Signal<fptype>::getReferenceTau()
{
	return _tau.valReference;
}

template<typename fptype>
fptype Signal<fptype>::getTau()
{
	return _tau.val;
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
	bool isTauDetected = false;
	for (fptype time = 0; time < timeOfSignal; time += Td)
	{
		if ((bitIdx == _tau.nReference) && (!isTauDetected))
		{
			isTauDetected = true;
			_tau.valReference = time;
		}

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

	fptype Esig = 0.0;
	fptype En = 0.0;

	for (size_t i = 0; i < size; ++i)
	{
		fptype M, ksi;
		M = rand() % 9 + 12;
		ksi = 0;
		for (int k = 0; k < M; k++)
		{
			ksi += (fptype)((rand() % 21 - 10) / 10.);
		}
		noise[i] = ksi / M;
		En += noise[i] * noise[i];
		Esig += _dataModulated[i] * _dataModulated[i];
	}

	//fptype alfa = sqrt(exp(log((fptype)10.0)*_par._SNR / 10.));
	fptype alfa = sqrt(pow(10, -_par._SNR/10) * Esig / En);

	for (size_t i = 0; i < size; ++i)
	{
		_dataModulated[i] += alfa * noise[i];
		_signalModulated[i].Y = _dataModulated[i];
	}
}
