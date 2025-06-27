#pragma once

#include <Windows.h>

class Timer
{
	LARGE_INTEGER start_time_;
	double frequency_;
public:

	Timer();

	void reset();
	double elapsed();
};