#include "BinaryGrid2.h"
#include "Math.h"

BinaryGrid2::BinaryGrid2(size_t width, size_t height) :
	_width(width),
	_height(height),
	_size((size_t)Math::ceil(_width* _height / 8.0)),
	_data(new uint8_t[_size])
{ }
BinaryGrid2::BinaryGrid2(size_t width, size_t height, bool value) :
	_width(width),
	_height(height),
	_size((size_t)Math::ceil(_width* _height / 8.0)),
	_data(new uint8_t[_size])
{
	std::fill(_data, _data + _size, value ? 255 : 0);
}
BinaryGrid2::BinaryGrid2(const BinaryGrid2& rhs) :
	_width(rhs._width),
	_height(rhs._height),
	_size(rhs._size),
	_data(new uint8_t[_size])
{
	std::copy(rhs._data, rhs._data + _size, _data);
}
BinaryGrid2& BinaryGrid2::operator=(const BinaryGrid2& rhs) {
	if (_width != rhs._width || _height != rhs._height) {
		delete[] _data;
		_width = rhs._width;
		_height = rhs._height;
		_size = rhs._size;
		_data = new uint8_t[_size];
	}

	std::copy(rhs._data, rhs._data + _size, _data);
	return *this;
}
BinaryGrid2::BinaryGrid2(BinaryGrid2&& rhs) :
	_width(rhs._width),
	_height(rhs._height),
	_size(rhs._size),
	_data(rhs._data)
{
	rhs._data = nullptr;
}
BinaryGrid2& BinaryGrid2::operator=(BinaryGrid2&& rhs) {
	delete[] _data;
	_width = rhs._width;
	_height = rhs._height;
	_size = rhs._size;
	_data = rhs._data;

	rhs._data = nullptr;
	return *this;
}
BinaryGrid2::~BinaryGrid2() {
	delete[] _data;
}

size_t BinaryGrid2::width() const {
	return _width;
}
size_t BinaryGrid2::height() const {
	return _height;
}

uint8_t* BinaryGrid2::data() const {
	return _data;
}
size_t BinaryGrid2::size() const {
	return _size;
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

std::ostream& operator<<(std::ostream& stream, const BinaryGrid2& rhs) {
	const size_t width = rhs.width();
	const size_t height = rhs.height();
	for (size_t y = 0; y < height; y++) {
		for (size_t x = 0; x < width; x++)
			stream << rhs.getTile(x, y) << " ";
		stream << std::endl;
	}
	return stream;
}