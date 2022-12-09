#include "Image4.h"
#include "Math.h"

Image4::Image4() :
	_width(1),
	_height(1),
	data(new uint8_t[4])
{ }
Image4::Image4(int width, int height) :
	_width(width),
	_height(height),
	data(new uint8_t[(uint64_t)width * (uint64_t)height * 4])
{ }
Image4::Image4(int width, int height, const Color4& color) :
	_width(width),
	_height(height),
	data(new uint8_t[(uint64_t)width * (uint64_t)height * 4])
{
	this->modify([&color](size_t x, size_t y, void* pixel) -> void {
		color.writeToPixel(pixel);
	});
}
Image4::Image4(int width, int height, uint8_t* data) :
	_width(width),
	_height(height),
	data(data)
{ }
Image4::Image4(const Image4& image) {
	copy(image);
}
Image4::~Image4() {
	delete[] this->data;
}

const Image4 Image4::none(1, 1, Color4::none);
const Image4 Image4::white(1, 1, Color4::white);
const Image4 Image4::black(1, 1, Color4::black);

int Image4::getWidth() const {
	return this->_width;
}
int Image4::getHeight() const {
	return this->_height;
}

void* Image4::pixelAt(size_t x, size_t y) const {
	if (x >= this->_width) return nullptr;
	else if (y >= this->_height) return nullptr;
	return (void*)(this->data + (x + y * this->_width) * 4);
}
Color4 Image4::colorAt(double t, double s) const {
	t -= Math::floor(t);
	s -= Math::floor(s);

	int x = (int)(t * _width);
	int y = (int)(s * _height);

	uint8_t* pixel = this->data + ((uint64_t)x + (uint64_t)y * this->_width) * 4;
	return Color4(pixel[0], pixel[1], pixel[2], pixel[3]);
}
void Image4::modify(const std::function<void(size_t, size_t, void*)>& func) {
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

Image4& Image4::operator=(const Image4& rhs) {
	delete[] this->data;
	copy(rhs);
	return *this;
}

void Image4::copy(const Image4& obj) {
	this->_width = obj.getWidth();
	this->_height = obj.getHeight();
	int size = this->_width * this->_height * 4;
	this->data = new uint8_t[size];
	std::copy(obj.data, obj.data + size, data);
}