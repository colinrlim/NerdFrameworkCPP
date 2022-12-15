#include "Image4.h"
#include "Math.h"
#include <iostream>

Image4::Image4() :
	_width(1),
	_height(1),
	_size(4),
	data(new uint8_t[_size])
{ }
Image4::Image4(int width, int height) :
	_width(width),
	_height(height),
	_size(width * height * 4),
	data(new uint8_t[_size])
{ }
Image4::Image4(int width, int height, const Color4& color) :
	_width(width),
	_height(height),
	_size(width * height * 4),
	data(new uint8_t[_size])
{
	this->modify([&color](void* pixel) -> void {
		color.writeToPixel(pixel);
	});
}
Image4::Image4(int width, int height, uint8_t* data) :
	_width(width),
	_height(height),
	_size(width * height * 4),
	data(data)
{ }
Image4::Image4(int width, int height, const std::vector<std::vector<uint8_t>>& map) :
	_width(width),
	_height(height),
	_size(width * height * 4),
	data(new uint8_t[_size])
{
	size_t rowSize = (size_t)(width * 4.0);
	for (size_t y = 0; y < height; y++) {
		const uint8_t* rowData = map[y].data();
		std::copy(rowData, rowData + rowSize, data + y * rowSize);
	}
}
Image4::Image4(int width, int height, std::vector<std::vector<uint8_t>>&& map) :
	_width(width),
	_height(height),
	_size(width * height * 4),
	data(new uint8_t[_size])
{
	size_t rowSize = (size_t)(width * 4.0);
	for (size_t y = 0; y < height; y++) {
		uint8_t* rowData = map[y].data();
		std::move(rowData, rowData + rowSize, data + y * rowSize);
	}
}
Image4::Image4(int width, int height, const std::vector<std::vector<uint32_t>>& map) :
	_width(width),
	_height(height),
	_size(width * height * 4),
	data(new uint8_t[_size])
{
	size_t rowSize = (size_t)(width * 4.0);
	for (size_t y = 0; y < height; y++) {
		const uint8_t* rowData = (uint8_t*)map[y].data();
		std::copy(rowData, rowData + rowSize, data + y * rowSize);
	}
}
Image4::Image4(int width, int height, std::vector<std::vector<uint32_t>>&& map) :
	_width(width),
	_height(height),
	_size(width * height * 4),
	data(new uint8_t[_size])
{
	size_t rowSize = (size_t)(width * 4.0);
	for (size_t y = 0; y < height; y++) {
		uint8_t* rowData = (uint8_t*)map[y].data();
		std::move(rowData, rowData + rowSize, data + y * rowSize);
	}
}
Image4::Image4(const Image4& rhs) :
	_width(rhs._width),
	_height(rhs._height),
	_size(rhs._size),
	data(new uint8_t[_size])
{
	std::copy(rhs.data, rhs.data + _size, data);
}
Image4& Image4::operator=(const Image4& rhs) {
	delete[] data;
	_width = rhs._width;
	_height = rhs._height;
	_size = rhs._size;
	data = new uint8_t[_size];
	std::copy(rhs.data, rhs.data + _size, data);
	return *this;
}
Image4::Image4(Image4&& rhs) :
	_width(rhs._width),
	_height(rhs._height),
	_size(rhs._size),
	data(rhs.data)
{
	rhs.data = nullptr;
}
Image4& Image4::operator=(Image4&& rhs) {
	delete[] data;
	_width = rhs._width;
	_height = rhs._height;
	_size = rhs._size;
	data = rhs.data;
	rhs.data = nullptr;
	return *this;
}
Image4::~Image4() {
	delete[] data;
}

const Image4 Image4::none(1, 1, Color4::none);
const Image4 Image4::white(1, 1, Color4::white);
const Image4 Image4::black(1, 1, Color4::black);

int Image4::width() const {
	return this->_width;
}
int Image4::height() const {
	return this->_height;
}
uint32_t Image4::size() const {
	return this->_size;
}

void* Image4::pixelAt(size_t x, size_t y) const {
	if (x >= this->_width) return nullptr;
	else if (y >= this->_height) return nullptr;
	return this->data + (x + y * this->_width) * 4;
}
Color4 Image4::colorAt(double t, double s) const {
	t -= Math::floor(t);
	s -= Math::floor(s);

	int x = (int)(t * _width);
	int y = (int)(s * _height);

	uint8_t* pixel = this->data + ((uint64_t)x + (uint64_t)y * this->_width) * 4;
	return Color4(pixel[0], pixel[1], pixel[2], pixel[3]);
}
void Image4::modify(const std::function<void(void*)>& func) {
	for (uint32_t i = 0; i < _size; i += 4)
		func(data + i);
}
void Image4::modify(const std::function<void(size_t, size_t, void*)>& func) {
	auto pixel = this->pixelAt(0, 0);
	size_t y = 0;
	while (pixel != nullptr) {
		size_t x = 0;
		while (pixel != nullptr) {
			func(x, y, pixel);
			x++;
			pixel = this->pixelAt(x, y);
		}
		x = 0;
		y++;
		pixel = this->pixelAt(x, y);
	}
}