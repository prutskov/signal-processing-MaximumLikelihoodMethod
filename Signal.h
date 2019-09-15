#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <cstdint>
#include <gdiplus.h>

using namespace Gdiplus;
using namespace std;

template <typename fptype>
class Signal
{
public:
	Signal(size_t nBits, fptype A, fptype f0, fptype bt, fptype fd);
	std::vector<uint8_t>* getData();
	std::vector<PointF>* getSignalPoints();
	virtual ~Signal();

private:
	void modulateSignal();


private:
	std::vector<fptype> _dataModulated;
	std::vector<PointF> _signalModulated;
	std::vector<uint8_t> _dataBits;

	fptype _f0;
	fptype _bt;
	fptype _fd;
	fptype _A;
};

