#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class Timer {
public:
	Timer();
	~Timer();
	float DelTime();
	void InitTimer();
private:
	long long prev_time;
};

#endif