#include <algorithm>
#include "Image3.h"
#include "Math.h"

Image3::Image3() :
	_width(1),
	_height(1),
	_size(3),
	data(new uint8_t[_size])
{ }
Image3::Image3(int width, int height) :
	_width(width),
	_height(height),
	_size(width * height * 3),
	data(new uint8_t[_size])
{ }
Image3::Image3(int width, int height, const Color3& color) :
	_width(width),
	_height(height),
	_size(width * height * 3),
	data(new uint8_t[_size])
{
	this->modify([&color](void* pixel) -> void {
		color.writeToPixel(pixel);
	});
}
Image3::Image3(int width, int height, uint8_t* data) :
	_width(width),
	_height(height),
	_size(width * height * 3),
	data(data)
{ }
Image3::Image3(int width, int height, const std::vector<uint8_t>& map) :
	_width(width),
	_height(height),
	_size(width * height * 3),
	data(new uint8_t[_size])
{
	std::copy(map.data(), map.data() + _size, data);
}
Image3::Image3(int width, int height, std::vector<uint8_t>&& map) :
	_width(width),
	_height(height),
	_size(width * height * 3),
	data(new uint8_t[_size])
{
	std::move(map.data(), map.data() + _size, data);
}
Image3::Image3(const PaletteImage& paletteImage, const Palette<Color3>& palette) :
	_width(paletteImage.width()),
	_height(paletteImage.height()),
	_size(_width* _height * 3),
	data(new uint8_t[_size])
{
	size_t size = paletteImage.size();
	for (size_t i = 0; i < size; i++)
		palette[paletteImage.data[i]].writeToPixel(data + i*3);
}
Image3::Image3(const Image3& rhs) :
	_width(rhs._width),
	_height(rhs._height),
	_size(rhs._size),
	data(new uint8_t[_size])
{
	std::copy(rhs.data, rhs.data + _size, data);
}
Image3& Image3::operator=(const Image3& rhs) {
	delete[] data;
	_width = rhs._width;
	_height = rhs._height;
	_size = rhs._size;
	data = new uint8_t[_size];
	std::copy(rhs.data, rhs.data + _size, data);
	return *this;
}
Image3::Image3(Image3&& rhs) :
	_width(rhs._width),
	_height(rhs._height),
	_size(rhs._size),
	data(rhs.data)
{
	rhs.data = nullptr;
}
Image3& Image3::operator=(Image3&& rhs) {
	delete[] data;
	_width = rhs._width;
	_height = rhs._height;
	_size = rhs._size;
	data = rhs.data;
	rhs.data = nullptr;
	return *this;
}
Image3::Image3(const Image3& rhs, const Rect2<int>& clipBounds) :
	_width(clipBounds.width),
	_height(clipBounds.height),
	_size(_width * _height * 3),
	data(new uint8_t[_size])
{
	for (int y = clipBounds.y; y < clipBounds.height; y++) {
		size_t begin = y * rhs._width * 3;
		size_t beginOffset = begin + clipBounds.x * 3;
		size_t endOffset = beginOffset + clipBounds.width * 3;
		std::copy(rhs.data + beginOffset, rhs.data + endOffset, data + begin);
	}
}
Image3::Image3(Image3&& rhs, const Rect2<int>& clipBounds) :
	_width(clipBounds.width),
	_height(clipBounds.height),
	_size(_width * _height * 3),
	data(new uint8_t[_size])
{
	for (int y = clipBounds.y; y < clipBounds.height; y++) {
		size_t begin = y * rhs._width * 3;
		size_t beginOffset = begin + clipBounds.x * 3;
		size_t endOffset = beginOffset + clipBounds.width * 3;
		std::move(rhs.data + beginOffset, rhs.data + endOffset, data + begin);
	}
}
Image3::Image3(const Image3& rhs, const UDim2& clipPosition, const UDim2& clipSize) :
	_width((int)clipSize.x.absolute(rhs.width())),
	_height((int)clipSize.y.absolute(rhs.height())),
	_size(_width * _height * 3),
	data(new uint8_t[_size])
{
	const Rect2<int> absoluteClipBounds(clipPosition, clipSize, _width, _height);
	for (int y = absoluteClipBounds.y; y < absoluteClipBounds.height; y++) {
		size_t begin = y * rhs._width * 3;
		size_t beginOffset = begin + absoluteClipBounds.x * 3;
		size_t endOffset = beginOffset + absoluteClipBounds.width * 3;
		std::copy(rhs.data + beginOffset, rhs.data + endOffset, data + begin);
	}
}
Image3::Image3(Image3&& rhs, const UDim2& clipPosition, const UDim2& clipSize) :
	_width((int)clipSize.x.absolute(rhs.width())),
	_height((int)clipSize.y.absolute(rhs.height())),
	_size(_width * _height * 3),
	data(new uint8_t[_size])
{
	const Rect2<int> absoluteClipBounds(clipPosition, clipSize, _width, _height);
	for (int y = absoluteClipBounds.y; y < absoluteClipBounds.height; y++) {
		size_t begin = y * rhs._width * 3;
		size_t beginOffset = begin + absoluteClipBounds.x * 3;
		size_t endOffset = beginOffset + absoluteClipBounds.width * 3;
		std::move(rhs.data + beginOffset, rhs.data + endOffset, data + begin);
	}
}
Image3::~Image3() {
	delete[] data;
}

const Image3 Image3::none(1, 1, Color3::none);
const Image3 Image3::white(1, 1, Color3::white);
const Image3 Image3::black(1, 1, Color3::black);

int Image3::width() const {
	return this->_width;
}
int Image3::height() const {
	return this->_height;
}
size_t Image3::size() const {
	return this->_size;
}

void* Image3::pixelAt(size_t x, size_t y) const {
	if (x >= this->_width) return nullptr;
	else if (y >= this->_height) return nullptr;
	return this->data + (x + y * this->_width) * 3;
}
Color3 Image3::atParameterization(double t, double s) const {
	t -= Math::floor(t);
	s -= Math::floor(s);

	int x = (int)(t * _width);
	int y = (int)(s * _height);

	return Color3(pixelAt(x, y));
}
void Image3::modify(const std::function<void(void*)>& func) {
	for (uint32_t i = 0; i < _size; i += 3)
		func(data + i);
}
void Image3::modify(const std::function<void(size_t, size_t, void*)>& func) {
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

void Image3::flipHorizontally() {
	for (int i = 0; i < _height; i++)
		Image3::reverse(data + i * _width * 3, data + (i + 1) * _width * 3);
}
void Image3::flipVertically() {
	for (int i = 0; i < _height / 2; i++)
		Image3::swap_ranges(data + i * _width * 3, data + (i + 1) * _width * 3, data + (_height - 1 - i) * _width * 3);
}
void Image3::flipBoth() {
	Image3::reverse(data, data + _width * _height * 3);
}

void Image3::reverse(uint8_t* first, uint8_t* last) {
	last -= 3;
	while (first < last) {
		std::swap_ranges(first, first + 3, last);
		first += 3;
		last -= 3;
	}
}
void Image3::swap_ranges(uint8_t* first1, uint8_t* last1, uint8_t* first2) {
	while (first1 != last1) {
		std::swap_ranges(first1, first1 + 3, first2);
		first1 += 3;
		first2 += 3;
	}
}