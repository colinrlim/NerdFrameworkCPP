#pragma once

#include "Color4.h"

struct Image4
{
private:
	int _width;
	int _height;
	uint32_t _size;

	void copy(const Image4& obj);
public:
	uint8_t* data;

	Image4();
	Image4(int width, int height);
	Image4(int width, int height, const Color4& color);
	Image4(int width, int height, uint8_t* data);
	Image4(const Image4& image);
	~Image4();

	int getWidth() const;
	int getHeight() const;
	uint32_t size() const;

	static const Image4 none;
	static const Image4 white;
	static const Image4 black;

	void* pixelAt(size_t x, size_t y) const;
	Color4 colorAt(double t, double s) const;
	void modify(const std::function<void(size_t, size_t, void*)>& func);

	Image4& operator=(const Image4& rhs);
};

