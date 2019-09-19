#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <cstdint>
#include <gdiplus.h>

using namespace Gdiplus;
using namespace std;

enum ModulationType
{
	Amplitude = 0,
	BPSK,
	MSK
};

template<typename fptype>
struct SignalParameter
{
	size_t _nBits;
	fptype _A;
	fptype _f0;
	fptype _bt;
	fptype _fd;
	fptype _SNR = (fptype)10.0;
	ModulationType _modulType;
};

template<typename fptype>
struct Tau
{
	size_t nReference = 0;
	fptype valReference = 0.0;
	fptype val = 0;
};

template <typename fptype>
class Signal
{
public:
	Signal(SignalParameter<fptype> params);
	Signal(Signal<fptype> *signal, SignalParameter<fptype> params, size_t tau);
	std::vector<uint8_t> getData();
	SignalParameter<fptype>* getParameters();
	std::vector<PointF>* getSignalPoints();
	std::vector<PointF>* getCorrelationPoints();
	fptype getCorrelation(Signal<fptype> *signal2);
	fptype getReferenceTau();
	fptype getTau();
	virtual ~Signal();

private:
	void modulateSignal();
	void modulateAM(fptype timeSignal, fptype TmodPerBit, fptype Td);
	void modulateBPSK(fptype timeSignal, fptype TmodPerBit, fptype Td);
	void modulateMSK(fptype timeSignal, fptype TmodPerBit, fptype Td);

	void generateNoise();

private:
	std::vector<fptype> _dataModulated;
	std::vector<PointF> _signalModulated;
	std::vector<PointF> _correlationPoints;
	std::vector<uint8_t> _dataBits;

	SignalParameter<fptype> _par;
	Tau<fptype> _tau;
};

