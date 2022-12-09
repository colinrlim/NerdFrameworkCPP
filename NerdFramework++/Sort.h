#pragma once

#include <functional>
#include <vector>

template <typename T>
class Sort
{
private:
	std::vector<T>& list;

	void swap(std::vector<T>& list, int index1, int index2);

	Sort();
public:
	static void bubble(std::vector<T>& list, const std::function<bool(T, T)>& conditionToSwap);
	static void selection(std::vector<T>& list, const std::function<int(T, T)>& conditionToSwap);
	static void insertion(std::vector<T>& list, const std::function<int(T, T)>& conditionToSwap);

	static std::vector<T> bubbled(const std::vector<T>& list, const std::function<bool(T, T)>& conditionToSwap);
	static std::vector<T> selectioned(const std::vector<T>& list, const std::function<int(T, T)>& conditionToSwap);
	static std::vector<T> insertioned(const std::vector<T>& list, const std::function<int(T, T)>& conditionToSwap);
};

