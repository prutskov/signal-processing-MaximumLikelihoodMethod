#pragma once
#include <vector>

template <typename fptype>
class Signal
{
public:
	Signal(const size_t size);
	std::vector<fptype>* getData();
	virtual ~Signal();

private:
	std::vector<fptype> _data;
};

