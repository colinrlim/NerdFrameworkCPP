#pragma once

#include <concepts>
#include "Math.h"

template<typename T>
struct NumericRange {
	T min;
	T max;

	NumericRange(const T& constant) :
		min(constant),
		max(constant)
	{ }
	NumericRange(const T& min, const T& max) :
		min(min),
		max(max)
	{ }

	T random() const {
		return T::fromRandom(min, max);
	}
	T randomArithmetic() const {
		return Math::random(min, max);
	}
};