#pragma once

#include <functional>
#include <thread>
#include <vector>

class Parallel
{
private:
	Parallel();
public:
	static void For(int fromInclusive, int toExclusive, const std::function<void(int)>& body);
	template <typename T> static void ForEach(std::vector<T>& source, const std::function<void(T&)>& body);
};

