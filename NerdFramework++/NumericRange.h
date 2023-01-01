#pragma once

template <typename T>
struct NumericRange {
	const T min;
	const T max;

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
};