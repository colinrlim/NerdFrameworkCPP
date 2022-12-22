#include "PaletteImage.h"
#include "Math.h"
#include <iostream>

PaletteImage::PaletteImage() :
	_width(1),
	_height(1),
	_size(1),
	data(new uint8_t[_size])
{ }
PaletteImage::PaletteImage(int width, int height) :
	_width(width),
	_height(height),
	_size(width * height),
	data(new uint8_t[_size])
{ }
PaletteImage::PaletteImage(int width, int height, uint8_t color) :
	_width(width),
	_height(height),
	_size(width * height),
	data(new uint8_t[_size])
{
	std::fill(data, data + _size, color);
}
PaletteImage::PaletteImage(int width, int height, uint8_t* data) :
	_width(width),
	_height(height),
	_size(width * height),
	data(data)
{ }
PaletteImage::PaletteImage(int width, int height, const std::vector<uint8_t>& map) :
	_width(width),
	_height(height),
	_size(width * height),
	data(new uint8_t[_size])
{
	std::copy(map.data(), map.data() + _size, data);
}
PaletteImage::PaletteImage(int width, int height, std::vector<uint8_t>&& map) :
	_width(width),
	_height(height),
	_size(width * height),
	data(new uint8_t[_size])
{
	std::move(map.data(), map.data() + _size, data);
}
PaletteImage::PaletteImage(const PaletteImage& rhs) :
	_width(rhs._width),
	_height(rhs._height),
	_size(rhs._size),
	data(new uint8_t[_size])
{
	std::copy(rhs.data, rhs.data + _size, data);
}
PaletteImage& PaletteImage::operator=(const PaletteImage& rhs) {
	delete[] data;
	_width = rhs._width;
	_height = rhs._height;
	_size = rhs._size;
	data = new uint8_t[_size];
	std::copy(rhs.data, rhs.data + _size, data);
	return *this;
}
PaletteImage::PaletteImage(PaletteImage&& rhs) :
	_width(rhs._width),
	_height(rhs._height),
	_size(rhs._size),
	data(rhs.data)
{
	rhs.data = nullptr;
}
PaletteImage& PaletteImage::operator=(PaletteImage&& rhs) {
	delete[] data;
	_width = rhs._width;
	_height = rhs._height;
	_size = rhs._size;
	data = rhs.data;
	rhs.data = nullptr;
	return *this;
}
PaletteImage::PaletteImage(const PaletteImage& rhs, const Rect2<int>& clipBounds) :
	_width(clipBounds.width),
	_height(clipBounds.height),
	_size(_width * _height),
	data(new uint8_t[_size])
{
	for (int y = clipBounds.y; y < clipBounds.height; y++) {
		size_t begin = y * rhs._width;
		size_t beginOffset = begin + clipBounds.x;
		size_t endOffset = beginOffset + clipBounds.width;
		std::copy(rhs.data + beginOffset, rhs.data + endOffset, data + begin);
	}
}
PaletteImage::PaletteImage(PaletteImage&& rhs, const Rect2<int>& clipBounds) :
	_width(clipBounds.width),
	_height(clipBounds.height),
	_size(_width * _height),
	data(new uint8_t[_size])
{
	for (int y = clipBounds.y; y < clipBounds.height; y++) {
		size_t begin = y * rhs._width;
		size_t beginOffset = begin + clipBounds.x;
		size_t endOffset = beginOffset + clipBounds.width;
		std::move(rhs.data + beginOffset, rhs.data + endOffset, data + begin);
	}
}
PaletteImage::PaletteImage(const PaletteImage& rhs, const UDim2& clipPosition, const UDim2& clipSize) :
	_width((int)clipSize.x.absolute(rhs.width())),
	_height((int)clipSize.y.absolute(rhs.height())),
	_size(_width * _height),
	data(new uint8_t[_size])
{
	const Rect2<int> absoluteClipBounds(clipPosition, clipSize, _width, _height);
	for (int y = absoluteClipBounds.y; y < absoluteClipBounds.height; y++) {
		size_t begin = y * rhs._width;
		size_t beginOffset = begin + absoluteClipBounds.x;
		size_t endOffset = beginOffset + absoluteClipBounds.width;
		std::copy(rhs.data + beginOffset, rhs.data + endOffset, data + begin);
	}
}
PaletteImage::PaletteImage(PaletteImage&& rhs, const UDim2& clipPosition, const UDim2& clipSize) :
	_width((int)clipSize.x.absolute(rhs.width())),
	_height((int)clipSize.y.absolute(rhs.height())),
	_size(_width * _height),
	data(new uint8_t[_size])
{
	const Rect2<int> absoluteClipBounds(clipPosition, clipSize, _width, _height);
	for (int y = absoluteClipBounds.y; y < absoluteClipBounds.height; y++) {
		size_t begin = y * rhs._width ;
		size_t beginOffset = begin + absoluteClipBounds.x;
		size_t endOffset = beginOffset + absoluteClipBounds.width;
		std::move(rhs.data + beginOffset, rhs.data + endOffset, data + begin);
	}
}
PaletteImage::~PaletteImage() {
	delete[] data;
}

const PaletteImage PaletteImage::none(1, 1, (uint8_t)0);
const PaletteImage PaletteImage::one(1, 1, 1);
const PaletteImage PaletteImage::two(1, 1, 2);
const PaletteImage PaletteImage::three(1, 1, 3);

int PaletteImage::width() const {
	return this->_width;
}
int PaletteImage::height() const {
	return this->_height;
}
size_t PaletteImage::size() const {
	return this->_size;
}

uint8_t* PaletteImage::pixelAt(size_t x, size_t y) const {
	if (x >= this->_width) return nullptr;
	else if (y >= this->_height) return nullptr;
	return this->data + (x + y * this->_width);
}
uint8_t PaletteImage::atParameterization(double t, double s) const {
	t -= Math::floor(t);
	s -= Math::floor(s);

	int x = (int)(t * _width);
	int y = (int)(s * _height);

	uint8_t* pixel = this->data + ((uint64_t)x + (uint64_t)y * this->_width);
	return *pixel;
}
void PaletteImage::modify(const std::function<void(uint8_t*)>& func) {
	for (uint32_t i = 0; i < _size; i++)
		func(data + i);
}
void PaletteImage::modify(const std::function<void(size_t, size_t, uint8_t*)>& func) {
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