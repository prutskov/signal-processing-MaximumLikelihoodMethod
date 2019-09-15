#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <cstdint>
#include <gdiplus.h>

using namespace Gdiplus;
using namespace std;

template<typename fptype>
struct SignalParameter
{
	size_t _nBits;
	fptype _A;
	fptype _f0;
	fptype _bt;
	fptype _fd;
};

template <typename fptype>
class Signal
{
public:
	Signal(SignalParameter<fptype> params);
	std::vector<uint8_t>* getData();
	SignalParameter<fptype> getParameters();
	std::vector<PointF>* getSignalPoints();
	virtual ~Signal();

private:
	void modulateSignal();


private:
	std::vector<fptype> _dataModulated;
	std::vector<PointF> _signalModulated;
	std::vector<uint8_t> _dataBits;

	SignalParameter<fptype> _par;
};

