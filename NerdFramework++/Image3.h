#pragma once

#include "Color3.h"

struct Image3
{
	uint8_t* data;

	Image3();
	Image3(int width, int height);
	Image3(int width, int height, const Color3& color);
	Image3(int width, int height, uint8_t* data);
	Image3(const Image3& image);
	~Image3();

	int getWidth() const;
	int getHeight() const;

	static const Image3 none;
	static const Image3 white;
	static const Image3 black;

	void* pixelAt(size_t x, size_t y) const;
	Color3 colorAt(double t, double s) const;
	void modify(const std::function<void(size_t, size_t, void*)>& func);

	Image3& operator=(const Image3& rhs);
private:
	int _width;
	int _height;

	void copy(const Image3& obj);
};

