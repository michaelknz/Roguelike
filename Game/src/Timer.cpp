#include "Timer.h"

Timer::Timer() {
	InitTimer();
}

Timer::~Timer() {

}

void Timer::InitTimer() {
	prev_time = SDL_GetTicks64();
}

float Timer::DelTime() {
	long long cur_time = SDL_GetTicks64();
	long long del = cur_time - prev_time;
	prev_time = cur_time;
	return (float)del / 1000.0f;
}