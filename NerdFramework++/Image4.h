#pragma once

#include "PaletteImage.h"
#include "Palette.h"
#include "Color4.h"
#include "Rect2.h"
#include "UDim2.h"

struct Image4
{
private:
	int _width;
	int _height;
	size_t _size;
public:
	uint8_t* data;

	Image4();
	Image4(int width, int height);
	Image4(int width, int height, const Color4& color);
	Image4(int width, int height, uint8_t* data);
	Image4(int width, int height, const std::vector<uint8_t>& map);
	Image4(int width, int height, std::vector<uint8_t>&& map);
	Image4(int width, int height, const std::vector<uint32_t>& map);
	Image4(int width, int height, std::vector<uint32_t>&& map);
	Image4(const PaletteImage& paletteImage, const Palette<Color4>& palette);
	Image4(const Image4& rhs);
	Image4& operator=(const Image4& rhs);
	Image4(Image4&& rhs);
	Image4& operator=(Image4&& rhs);
	Image4(const Image4& rhs, const Rect2<int>& clipBounds);
	Image4(Image4&& rhs, const Rect2<int>& clipBounds);
	Image4(const Image4& rhs, const UDim2& clipPosition, const UDim2& clipSize);
	Image4(Image4&& rhs, const UDim2& clipPosition, const UDim2& clipSize);
	~Image4();

	int width() const;
	int height() const;
	size_t size() const;

	static const Image4 none;
	static const Image4 white;
	static const Image4 black;

	void* pixelAt(size_t x, size_t y) const;
	Color4 atParameterization(double t, double s) const;
	void modify(const std::function<void(void*)>& func);
	void modify(const std::function<void(size_t, size_t, void*)>& func);

	void flipHorizontally();
	void flipVertically();
	void flipBoth();
};

