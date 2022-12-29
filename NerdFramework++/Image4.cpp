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
Image4::Image4(int width, int height, const std::vector<uint8_t>& map) :
	_width(width),
	_height(height),
	_size(width * height * 4),
	data(new uint8_t[_size])
{
	std::copy(map.data(), map.data() + _size, data);
}
Image4::Image4(int width, int height, std::vector<uint8_t>&& map) :
	_width(width),
	_height(height),
	_size(width * height * 4),
	data(new uint8_t[_size])
{
	std::move(map.data(), map.data() + _size, data);
}
Image4::Image4(int width, int height, const std::vector<uint32_t>& map) :
	_width(width),
	_height(height),
	_size(width * height * 4),
	data(new uint8_t[_size])
{
	uint8_t* castedMapData = (uint8_t*)map.data();
	std::copy(castedMapData, castedMapData + _size, data);
}
Image4::Image4(int width, int height, std::vector<uint32_t>&& map) :
	_width(width),
	_height(height),
	_size(width * height * 4),
	data(new uint8_t[_size])
{
	uint8_t* castedMapData = (uint8_t*)map.data();
	std::move(castedMapData, castedMapData + _size, data);
}
Image4::Image4(const PaletteImage& paletteImage, const Palette<Color4>& palette) :
	_width(paletteImage.width()),
	_height(paletteImage.height()),
	_size(_width * _height * 4),
	data(new uint8_t[_size])
{
	size_t size = paletteImage.size();
	for (int i = 0; i < size; i++)
		palette[paletteImage.data[i]].writeToPixel(data + i * 4);
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
Image4::Image4(const Image4& rhs, const Rect2<int>& clipBounds) :
	_width(clipBounds.width),
	_height(clipBounds.height),
	_size(_width * _height * 4),
	data(new uint8_t[_size])
{
	for (int y = clipBounds.y; y < clipBounds.height; y++) {
		size_t begin = y * rhs._width * 4;
		size_t beginOffset = begin + clipBounds.x * 4;
		size_t endOffset = beginOffset + clipBounds.width * 4;
		std::copy(rhs.data + beginOffset, rhs.data + endOffset, data + begin);
	}
}
Image4::Image4(Image4&& rhs, const Rect2<int>& clipBounds) :
	_width(clipBounds.width),
	_height(clipBounds.height),
	_size(_width * _height * 4),
	data(new uint8_t[_size])
{
	for (int y = clipBounds.y; y < clipBounds.height; y++) {
		size_t begin = y * rhs._width * 4;
		size_t beginOffset = begin + clipBounds.x * 4;
		size_t endOffset = beginOffset + clipBounds.width * 4;
		std::move(rhs.data + beginOffset, rhs.data + endOffset, data + begin);
	}
}
Image4::Image4(const Image4& rhs, const UDim2& clipPosition, const UDim2& clipSize) :
	_width((int)clipSize.x.absolute(rhs.width())),
	_height((int)clipSize.y.absolute(rhs.height())),
	_size(_width * _height * 4),
	data(new uint8_t[_size])
{
	const Rect2<int> absoluteClipBounds(clipPosition, clipSize, _width, _height);
	for (int y = absoluteClipBounds.y; y < absoluteClipBounds.height; y++) {
		size_t begin = y * rhs._width * 4;
		size_t beginOffset = begin + absoluteClipBounds.x * 4;
		size_t endOffset = beginOffset + absoluteClipBounds.width * 4;
		std::copy(rhs.data + beginOffset, rhs.data + endOffset, data + begin);
	}
}
Image4::Image4(Image4&& rhs, const UDim2& clipPosition, const UDim2& clipSize) :
	_width((int)clipSize.x.absolute(rhs.width())),
	_height((int)clipSize.y.absolute(rhs.height())),
	_size(_width * _height * 4),
	data(new uint8_t[_size])
{
	const Rect2<int> absoluteClipBounds(clipPosition, clipSize, _width, _height);
	for (int y = absoluteClipBounds.y; y < absoluteClipBounds.height; y++) {
		size_t begin = y * rhs._width * 4;
		size_t beginOffset = begin + absoluteClipBounds.x * 4;
		size_t endOffset = beginOffset + absoluteClipBounds.width * 4;
		std::move(rhs.data + beginOffset, rhs.data + endOffset, data + begin);
	}
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
size_t Image4::size() const {
	return this->_size;
}

void* Image4::pixelAt(size_t x, size_t y) const {
	if (x >= this->_width) return nullptr;
	else if (y >= this->_height) return nullptr;
	return this->data + (x + y * this->_width) * 4;
}
Color4 Image4::atParameterization(double t, double s) const {
	t -= Math::floor(t);
	s -= Math::floor(s);

	int x = (int)(t * _width);
	int y = (int)(s * _height);

	return Color4(pixelAt(x, y));
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