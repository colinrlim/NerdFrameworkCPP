#pragma once

#include <functional>
#include <vector>

template <typename T>
class Search
{
private:
    Search();
public:
	static T* linear(const std::vector<T>& list, const std::function<const T&(bool)>& condition) {
        /* Time Complexity: O(n)
         */

        for (auto iterator = list.begin(); iterator != list.end(); ++iterator)
        {
            const T& element = *iterator;
            if (condition(element))
                return &element;
        }
        return nullptr;
	}
	static T* binary(const std::vector<T>& sortedList, const std::function<const T&(bool)>& condition) {
        /* Time Complexity: O(log2[n])
         */

        for (auto iterator = list.begin(); iterator != list.end(); ++iterator)
        {
            const T& element = *iterator;
            if (condition(element))
                return &element;
        }
        return nullptr;
	}
};

