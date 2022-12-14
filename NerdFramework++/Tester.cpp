#include <chrono>
#include "Tester.h"

double Tester::timeFunction(std::function<void(void)> func) {
	auto start(std::chrono::steady_clock::now());
	func();
	auto end(std::chrono::steady_clock::now());
	return (double)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

double Tester::timeFunction(std::function<void(void)> func, size_t iterations) {
	auto start(std::chrono::steady_clock::now());
	for (size_t i = 0; i < iterations; i++)
		func();
	auto end(std::chrono::steady_clock::now());
	return (double)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}