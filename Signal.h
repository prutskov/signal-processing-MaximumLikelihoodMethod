#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <gdiplus.h>

using namespace Gdiplus;

template <typename fptype>
class Signal
{
public:
	Signal(size_t nBits, fptype A, fptype f0, fptype bt, fptype fd);
	std::vector<unsigned char>* getData();
	std::vector<PointF>* getSignalPoints();
	virtual ~Signal();

private:
	void modulateSignal();


private:
	std::vector<fptype> _dataModulated;
	std::vector<PointF> _signalModulated;
	std::vector<unsigned char> _dataBits;

	fptype _f0;
	fptype _bt;
	fptype _fd;
	fptype _A;
};

