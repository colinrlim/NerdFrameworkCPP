#pragma once

#include <ostream>

template <typename T>
struct QuickGrid2 {
private:
	size_t _width;
	size_t _height;
	size_t _size;

	T _defaultValue;
	T** _data;
public:
	QuickGrid2(size_t width, size_t height) :
		_width(width),
		_height(height),
		_size(_width * _height),
		_defaultValue(),
		_data(new T*[_size]())
	{
		//std::fill(_data, _data + _size, &_defaultValue);
	}
	QuickGrid2(size_t width, size_t height, const T& defaultValue) :
		_width(width),
		_height(height),
		_size(_width * _height),
		_defaultValue(defaultValue),
		_data(new T*[_size]())
	{
		//std::fill(_data, _data + _size, &_defaultValue);
	}
	QuickGrid2(const QuickGrid2& rhs) :
		_width(rhs._width),
		_height(rhs._height),
		_size(rhs._size),
		_defaultValue(rhs._defaultValue),
		_data(new T*[_size])
	{
		std::copy(rhs._data, rhs._data + _size, _data);
	}
	QuickGrid2& operator=(const QuickGrid2& rhs) {
		delete[] _data;
		_width = rhs._width;
		_height = rhs._height;
		_size = rhs._size;
		_defaultValue = rhs._defaultValue;
		_data = new T*[_size];

		std::copy(rhs._data, rhs._data + _size, _data);
		return *this;
	}
	QuickGrid2(QuickGrid2&& rhs) :
		_width(rhs._width),
		_height(rhs._height),
		_size(rhs._size),
		_defaultValue(std::move(rhs._defaultValue)),
		_data(rhs._data)
	{
		rhs._data = nullptr;
	}
	QuickGrid2& operator=(QuickGrid2&& rhs) {
		delete[] _data;
		_width = rhs._width;
		_height = rhs._height;
		_size = rhs._size;
		_defaultValue = std::move(rhs._defaultValue);
		_data = rhs._data;

		rhs._data = nullptr;
		return *this;
	}
	~QuickGrid2() {
		delete[] _data;
	}

	size_t width() const {
		return _width;
	}
	size_t height() const {
		return _height;
	}

	T** data() const {
		return _data;
	}
	size_t size() const {
		return _size;
	}

	const T& get(size_t x, size_t y) const {
		T* ptr = *(_data + x + y * _width);
		if (ptr == nullptr)
			return _defaultValue;
		return *ptr;
	}
	void set(size_t x, size_t y, const T& value) {
		T* ptr = *(_data + x + y * _width);
		ptr = new T(value);
	}
	void set(size_t x, size_t y, T&& value) {
		T* ptr = *(_data + x + y * _width);
		ptr = new T(std::move(value));
	}
	void reset() {
		std::fill(_data, _data + _size, nullptr);
	}
};

template <typename T>
std::ostream& operator<<(std::ostream& stream, const QuickGrid2<T>& rhs) {
	size_t width = rhs.width();
	size_t height = rhs.height();
	for (size_t y = 0; y < height; y++) {
		for (size_t x = 0; x < width; x++)
			stream << rhs.get(x, y) << " ";
		stream << std::endl;
	}
	return stream;
}

