#pragma once

#include <functional>

class Tester {
private:
	Tester();
public:
	static double timeFunction(std::function<void(void)> func);
	static double timeFunction(std::function<void(void)> func, size_t iterations);
};