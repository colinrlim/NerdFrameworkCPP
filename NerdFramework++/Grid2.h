#pragma once

template <typename T>
struct Grid2 {
private:
	size_t _width;
	size_t _height;
	T* _data;
public:
	Grid2(size_t width, size_t height) :
		_width(width),
		_height(height),
		_data(new T[size()])
	{ }
	Grid2(size_t width, size_t height, const T& defaultValue) :
		_width(width),
		_height(height),
		_data(new T[size()])
	{
		std::fill(_data, _data + size(), defaultValue);
	}
	Grid2(const Grid2& rhs) :
		_width(rhs._width),
		_height(rhs._height),
		_data(new T[size()])
	{
		std::copy(rhs._data, rhs._data + size(), _data);
	}
	Grid2& operator=(const Grid2& rhs) {
		_width = rhs._width;
		_height = rhs._height;
		delete[] _data;
		size_t size = this->size();
		_data = new T[size];
		std::copy(rhs._data, rhs._data + size, _data);
		return *this;
	}
	~Grid2() {
		delete[] _data;
	}

	size_t getWidth() const {
		return _width;
	}
	size_t getHeight() const {
		return _height;
	}

	T* data() const {
		return _data;
	}
	size_t size() const {
		return _width * _height;
	}

	T& at(size_t x, size_t y) {
		return *(_data + x + y * _width);
	}
};

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Grid2<T>& rhs) {
	size_t width = rhs.getWidth();
	size_t height = rhs.getHeight();
	for (size_t y = 0; y < height; y++) {
		for (size_t x = 0; x < width; x++)
			stream << rhs.at(x, y) << " ";
		stream << std::endl;
	}
	return stream;
}

