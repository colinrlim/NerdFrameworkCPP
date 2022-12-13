#pragma once

template <typename T>
struct Grid2 {
private:
	size_t _width;
	size_t _height;
	size_t _size;
	T* _data;
public:
	Grid2(size_t width, size_t height) :
		_width(width),
		_height(height),
		_size(_width * _height),
		_data(new T[_size])
	{ }
	Grid2(size_t width, size_t height, const T& defaultValue) :
		_width(width),
		_height(height),
		_size(_width * _height),
		_data(new T[_size])
	{
		std::fill(_data, _data + _size, defaultValue);
	}
	Grid2(const Grid2& rhs) :
		_width(rhs._width),
		_height(rhs._height),
		_size(rhs._size),
		_data(new T[_size])
	{
		std::copy(rhs._data, rhs._data + _size, _data);
	}
	Grid2& operator=(const Grid2& rhs) {
		delete[] _data;
		_width = rhs._width;
		_height = rhs._height;
		_size = rhs._size;
		_data = new T[_size];

		std::copy(rhs._data, rhs._data + _size, _data);
		return *this;
	}
	~Grid2() {
		delete[] _data;
	}

	size_t width() const {
		return _width;
	}
	size_t height() const {
		return _height;
	}

	T* data() const {
		return _data;
	}
	size_t size() const {
		return _size;
	}

	T& get(size_t x, size_t y) const {
		return *(_data + x + y * _width);
	}
};

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Grid2<T>& rhs) {
	size_t width = rhs.width();
	size_t height = rhs.height();
	for (size_t y = 0; y < height; y++) {
		for (size_t x = 0; x < width; x++)
			stream << rhs.get(x, y) << " ";
		stream << std::endl;
	}
	return stream;
}

