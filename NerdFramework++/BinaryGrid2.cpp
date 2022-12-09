#include "BinaryGrid2.h"
#include "Math.h"

BinaryGrid2::BinaryGrid2(size_t width, size_t height) :
	_width(width),
	_height(height),
	_data(new uint8_t[size()])
{ }
BinaryGrid2::BinaryGrid2(const BinaryGrid2& rhs) :
	_width(rhs._width),
	_height(rhs._height)
{
	size_t size = this->size();
	_data = new uint8_t[size];
	std::copy(rhs._data, rhs._data + size, _data);
}
BinaryGrid2& BinaryGrid2::operator=(const BinaryGrid2& rhs) {
	_width = rhs._width;
	_height = rhs._height;
	delete[] _data;
	size_t size = this->size();
	_data = new uint8_t[size];
	std::copy(rhs._data, rhs._data + size, _data);
	return *this;
}
BinaryGrid2::~BinaryGrid2() {
	delete[] _data;
}

size_t BinaryGrid2::getWidth() const {
	return _width;
}
size_t BinaryGrid2::getHeight() const {
	return _height;
}

uint8_t* BinaryGrid2::data() const {
	return _data;
}
size_t BinaryGrid2::size() const {
	return (size_t)Math::ceil(_width * _height / 8.0);
}

bool BinaryGrid2::getTile(size_t x, size_t y) const {
	size_t tileIndex = x + y * _width;
	size_t chunkIndex = tileIndex / 8;
	tileIndex -= chunkIndex * 8;
	return (bool)((*(_data + chunkIndex) & (1 << tileIndex)) >> tileIndex);
}
void BinaryGrid2::setTile(size_t x, size_t y, bool value) {
	size_t tileIndex = x + y * _width;
	size_t chunkIndex = tileIndex / 8;
	tileIndex -= chunkIndex * 8;
	if (value)
		*(_data + chunkIndex) |= (1 << tileIndex);
	else
		*(_data + chunkIndex) &= ~(1 << tileIndex);
}