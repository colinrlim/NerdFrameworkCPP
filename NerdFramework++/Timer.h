#pragma once

#include <functional>
#include <chrono>

class Timer {
private:
	std::chrono::steady_clock::time_point _init;
	double _offset;
public:
	Timer();

	void tickTo(std::chrono::steady_clock::time_point timepoint);
	void tickNow();
	void tickForward(double seconds);
	double tock() const;

	static double measureFunction(std::function<void(void)> func);
	static double measureFunction(std::function<void(void)> func, size_t iterations);
};