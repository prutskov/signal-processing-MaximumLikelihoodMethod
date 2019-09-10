#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

template <typename fptype>
class Signal
{
public:
	Signal(const size_t size);
	std::vector<unsigned char>* getData();
	virtual ~Signal();

private:
	void modulateSignal();


private:
	std::vector<fptype> _dataModulated;
	std::vector<unsigned char> _dataBits;

	fptype _f0;
	fptype _bt;
	fptype _fd;
	fptype _A;
};

