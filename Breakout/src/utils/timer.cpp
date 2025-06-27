#include "timer.h"

Timer::Timer()
{
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	frequency_ = 1.0 / frequency.QuadPart;
	QueryPerformanceCounter(&start_time_);
}

void Timer::reset()
{
	QueryPerformanceCounter(&start_time_);
}

double Timer::elapsed()
{
	LARGE_INTEGER end_time;
	QueryPerformanceCounter(&end_time);

	return (end_time.QuadPart - start_time_.QuadPart) * frequency_;
}