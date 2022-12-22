#pragma once

#include <functional>
#include "Rect2.h"

class PaletteImage {
private:
	int _width;
	int _height;
	size_t _size;
public:
	uint8_t* data;

	PaletteImage();
	PaletteImage(int width, int height);
	PaletteImage(int width, int height, uint8_t color);
	PaletteImage(int width, int height, uint8_t* data);
	PaletteImage(int width, int height, const std::vector<uint8_t>& map);
	PaletteImage(int width, int height, std::vector<uint8_t>&& map);
	PaletteImage(const PaletteImage& rhs);
	PaletteImage& operator=(const PaletteImage& rhs);
	PaletteImage(PaletteImage&& rhs);
	PaletteImage& operator=(PaletteImage&& rhs);
	PaletteImage(const PaletteImage& rhs, const Rect2<int>& clipBounds);
	PaletteImage(PaletteImage&& rhs, const Rect2<int>& clipBounds);
	PaletteImage(const PaletteImage& rhs, const UDim2& clipPosition, const UDim2& clipSize);
	PaletteImage(PaletteImage&& rhs, const UDim2& clipPosition, const UDim2& clipSize);
	~PaletteImage();

	int width() const;
	int height() const;
	size_t size() const;

	static const PaletteImage none;
	static const PaletteImage one;
	static const PaletteImage two;
	static const PaletteImage three;

	uint8_t* pixelAt(size_t x, size_t y) const;
	uint8_t atParameterization(double t, double s) const;
	void modify(const std::function<void(uint8_t*)>& func);
	void modify(const std::function<void(size_t, size_t, uint8_t*)>& func);
};

