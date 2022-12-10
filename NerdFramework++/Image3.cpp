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
	_size((size_t)_width* _height * 3),
	data(new uint8_t[_size])
{ }
Image3::Image3(int width, int height, const Color3& color) :
	_width(width),
	_height(height),
	_size((size_t)_width* _height * 3),
	data(new uint8_t[_size])
{
	this->modify([&color](size_t x, size_t y, void* pixel) -> void {
		color.writeToPixel(pixel);
	});
}
Image3::Image3(int width, int height, uint8_t* data) :
	_width(width),
	_height(height),
	data(data)
{ }
Image3::Image3(const Image3& image) {
	copy(image);
}
Image3::~Image3() {
	delete[] this->data;
}

const Image3 Image3::none(1, 1, Color3::none);
const Image3 Image3::white(1, 1, Color3::white);
const Image3 Image3::black(1, 1, Color3::black);

int Image3::getWidth() const {
	return this->_width;
}
int Image3::getHeight() const {
	return this->_height;
}
size_t Image3::size() const {
	return this->_size;
}

void* Image3::pixelAt(size_t x, size_t y) const {
	if (x >= this->_width) return nullptr;
	else if (y >= this->_height) return nullptr;
	return (void*)(this->data + (x + y * this->_width) * 3);
}
Color3 Image3::colorAt(double t, double s) const {
	t -= Math::floor(t);
	s -= Math::floor(s);

	int x = (int)(t * _width);
	int y = (int)(s * _height);

	uint8_t* pixel = this->data + ((uint64_t)x + (uint64_t)y * this->_width) * 3;
	return Color3(pixel[0], pixel[1], pixel[2]);
}
void Image3::modify(const std::function<void(size_t, size_t, void*)>& func) {
	auto pixel = (uint8_t*)this->pixelAt(0, 0);
	size_t y = 0;
	while (pixel != nullptr) {
		size_t x = 0;
		while (pixel != nullptr) {
			func(x, y, pixel);
			x++;
			pixel = (uint8_t*)this->pixelAt(x, y);
		}
		x = 0;
		y++;
		pixel = (uint8_t*)this->pixelAt(x, y);
	}
}

Image3& Image3::operator=(const Image3& rhs) {
	delete[] this->data;
	copy(rhs);
	return *this;
}

void Image3::copy(const Image3& obj) {
	this->_width = obj.getWidth();
	this->_height = obj.getHeight();
	int size = this->_width * this->_height * 3;
	this->data = new uint8_t[size];
	std::copy(obj.data, obj.data + size, data);
}