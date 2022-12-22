#pragma once

#include <vector>

template <typename T>
struct Palette {
	std::vector<T> colors;

	Palette() : colors() { }
	Palette(const std::vector<T>& colors) : colors(colors) { }
	Palette(std::vector<T>&& colors) : colors(std::move(colors)) { }

	const T& operator[](size_t index) const {
		return *(colors.data() + index);
	}
};

