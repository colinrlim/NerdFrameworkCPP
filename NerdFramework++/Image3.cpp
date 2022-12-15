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
Image3::Image3(int width, int height, const std::vector<std::vector<uint8_t>>& map) :
	_width(width),
	_height(height),
	_size(width * height * 3),
	data(new uint8_t[_size])
{
	size_t rowSize = (size_t)(width * 3.0);
	for (size_t y = 0; y < height; y++) {
		const uint8_t* rowData = map[y].data();
		std::copy(rowData, rowData + rowSize, data + y * rowSize);
	}
}
Image3::Image3(int width, int height, std::vector<std::vector<uint8_t>>&& map) :
	_width(width),
	_height(height),
	_size(width * height * 3),
	data(new uint8_t[_size])
{
	size_t rowSize = (size_t)(width * 3.0);
	for (size_t y = 0; y < height; y++) {
		uint8_t* rowData = map[y].data();
		std::move(rowData, rowData + rowSize, data + y * rowSize);
	}
}
Image3::Image3(int width, int height, const std::vector<std::vector<uint32_t>>& map) :
	_width(width),
	_height(height),
	_size(width * height * 3),
	data(new uint8_t[_size])
{
	size_t rowSize = (size_t)(width * 3.0);
	for (size_t y = 0; y < height; y++) {
		const uint8_t* rowData = (uint8_t*)map[y].data();
		std::copy(rowData, rowData + rowSize, data + y * rowSize);
	}
}
Image3::Image3(int width, int height, std::vector<std::vector<uint32_t>>&& map) :
	_width(width),
	_height(height),
	_size(width * height * 3),
	data(new uint8_t[_size])
{
	size_t rowSize = (size_t)(width * 3.0);
	for (size_t y = 0; y < height; y++) {
		uint8_t* rowData = (uint8_t*)map[y].data();
		std::move(rowData, rowData + rowSize, data + y * rowSize);
	}
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
Image3::Image3(const Image3& rhs, const Rect2<size_t>& clipBounds) :
	_width(clipBounds.width),
	_height(clipBounds.height),
	_size(_width * _height * 3),
	data(new uint8_t[_size])
{
	for (size_t y = clipBounds.y; y < clipBounds.height; y++) {
		size_t begin = y * rhs._width * 3;
		size_t beginOffset = begin + clipBounds.x * 3;
		size_t endOffset = beginOffset + clipBounds.width * 3;
		std::copy(rhs.data + beginOffset, rhs.data + endOffset, data + begin);
	}
}
Image3::Image3(Image3&& rhs, const Rect2<size_t>& clipBounds) :
	_width(clipBounds.width),
	_height(clipBounds.height),
	_size(_width * _height * 3),
	data(new uint8_t[_size])
{
	for (size_t y = clipBounds.y; y < clipBounds.height; y++) {
		size_t begin = y * rhs._width * 3;
		size_t beginOffset = begin + clipBounds.x * 3;
		size_t endOffset = beginOffset + clipBounds.width * 3;
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
uint32_t Image3::size() const {
	return this->_size;
}

void* Image3::pixelAt(size_t x, size_t y) const {
	if (x >= this->_width) return nullptr;
	else if (y >= this->_height) return nullptr;
	return this->data + (x + y * this->_width) * 3;
}
Color3 Image3::colorAt(double t, double s) const {
	t -= Math::floor(t);
	s -= Math::floor(s);

	int x = (int)(t * _width);
	int y = (int)(s * _height);

	uint8_t* pixel = this->data + ((uint64_t)x + (uint64_t)y * this->_width) * 3;
	return Color3(pixel[0], pixel[1], pixel[2]);
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