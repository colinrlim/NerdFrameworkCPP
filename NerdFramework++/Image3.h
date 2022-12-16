#pragma once

#include "Color3.h"
#include "Rect2.h"

struct Image3
{
private:
	int _width;
	int _height;
	size_t _size;
public:
	uint8_t* data;

	Image3();
	Image3(int width, int height);
	Image3(int width, int height, const Color3& color);
	Image3(int width, int height, uint8_t* data);
	Image3(int width, int height, const std::vector<std::vector<uint8_t>>& map);
	Image3(int width, int height, std::vector<std::vector<uint8_t>>&& map);
	Image3(int width, int height, const std::vector<std::vector<uint32_t>>& map);
	Image3(int width, int height, std::vector<std::vector<uint32_t>>&& map);
	Image3(const Image3& rhs);
	Image3& operator=(const Image3& rhs);
	Image3(Image3&& rhs);
	Image3& operator=(Image3&& rhs);
	Image3(const Image3& rhs, const Rect2<int>& clipBounds);
	Image3(Image3&& rhs, const Rect2<int>& clipBounds);
	~Image3();

	int width() const;
	int height() const;
	size_t size() const;

	static const Image3 none;
	static const Image3 white;
	static const Image3 black;

	void* pixelAt(size_t x, size_t y) const;
	Color3 colorAt(double t, double s) const;
	void modify(const std::function<void(void*)>& func);
	void modify(const std::function<void(size_t, size_t, void*)>& func);
};

