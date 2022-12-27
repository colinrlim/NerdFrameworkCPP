#include <chrono>
#include "Timer.h"

Timer::Timer() : _offset() { }

void Timer::tickTo(std::chrono::steady_clock::time_point timepoint) {
	_init = timepoint;
}
void Timer::tickNow() {
	_init = std::chrono::steady_clock::now();
}
void Timer::tickForward(double seconds) {
	_offset += seconds;
}
double Timer::tock() const {
	return (double)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - _init).count() / 1000.0 + _offset;
}

double Timer::measureFunction(std::function<void(void)> func) {
	auto start(std::chrono::steady_clock::now());
	func();
	auto end(std::chrono::steady_clock::now());
	return (double)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

double Timer::measureFunction(std::function<void(void)> func, size_t iterations) {
	auto start(std::chrono::steady_clock::now());
	for (size_t i = 0; i < iterations; i++)
		func();
	auto end(std::chrono::steady_clock::now());
	return (double)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}