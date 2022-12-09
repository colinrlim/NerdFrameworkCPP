#pragma once

#include <functional>
#include <vector>

template <typename T>
class List {
private:
	T* _data;
	size_t _capacity;
	size_t _size;

	void setCapacity(size_t amount) {
		_capacity = amount;
		T* newData = new T[_capacity];
		for (size_t i = 0; i < _size; i++) {
			*(newData + i) = *(_data + i);
		}
		delete[] _data;
		_data = newData;
	}
	void erase(T* ptr) {
		for (T* i = ptr + 1; i != _data + _size; i++)
			*i = *(i + 1);
		_size--;
	}

	friend class Iterator;
public:
	struct Iterator {
	private:
		T* _element_ptr;
		Iterator(T* element_ptr) :
			_element_ptr(element_ptr)
		{ }
	public:
		T operator*() { return *_element_ptr; }
		void operator+() { _element_ptr++; }
		void operator-() { _element_ptr--; }
		void operator==(const Iterator& rhs) { return _element_ptr == rhs._element_ptr; }
	};

	List() :
		_data(new T[1]),
		_capacity(1),
		_size(0)
	{ }
	List(size_t size) :
		_data(new T[size]()),
		_capacity(size),
		_size(size)
	{ }
	List(size_t size, T initialElementValue) :
		_data(new T[size]),
		_capacity(size),
		_size(size)
	{
		for (size_t i = 0; i < size; i++)
			*(_data + i) = initialElementValue;
	}
	List(const std::vector<T>& vector) :
		_data(vector.data()),
		_capacity(vector.capacity()),
		_size(vector.size())
	{}
	List(const List& rhs) :
		_data(rhs._size),
		_capacity(rhs._capacity),
		_size(rhs._size)
	{ }
	List& operator=(const List& rhs) {
		delete[] _data;
		_data = new T[rhs._size];
		for (size_t i = 0; i < rhs._size; i++)
			*(_data + i) = *(rhs._data + i);
		_size = rhs._size;
		_capacity = rhs._capacity;
		return *this;
	}
	~List() { delete[] _data; }

	void push_back(const T& element) {
		if (_size == _capacity)
			setCapacity(_capacity * 2);
		*(_data + _size) = element;
		_size++;
	}
	void pop_back() {
		_size--;
	}
	Iterator begin() const {
		return Iterator(_data);
	}
	Iterator end() const {
		return Iterator(_data + _size);
	}
	bool empty() const {
		return _size == 0;
	}
	T* data() const {
		return _data;
	}
	size_t size() const {
		return _size;
	}
	size_t capacity() const {
		return _capacity;
	}
	void clear() {
		_size = 0;
	}
	Iterator insert(size_t position, T element) {
		if (_size == _capacity)
			setCapacity(_capacity * 2);
		for (size_t i = _size - 1; i >= position; i--)
			*(_data + i + 1) = *(_data + i);
		*(_data + position) = element;
	}
	Iterator erase(size_t position) {
		erase(_data + position);
	}
	Iterator erase(Iterator iterator) {
		erase(iterator._element_ptr);
	}
	void resize(size_t newSize) {
		if (newSize < _size) return;
		_capacity = newSize;
		_size = newSize;
		T* newData = new T[_capacity]();
		for (size_t i = 0; i < _size; i++) {
			*(newData + i) = *(_data + i);
		}
		delete[] _data;
		_data = newData;
	}
	void reserve(size_t newCapacity) {
		if (newCapacity < _size) return;
		setCapacity(newCapacity);
	}
	T& find(const std::function<bool(T*)>& condition) const {
		for (size_t i = 0; i < _size; i++) {
			T* element = _data + i;
			if (condition(element))
				return *element;
		}
		return nullptr;
	}
	size_t findIndex(const std::function<bool(T*)>& condition) const {
		for (size_t i = 0; i < _size; i++)
			if (condition(_data + i))
				return i;
		return nullptr;
	}
	T& find(const std::function<bool(const T&)>& condition) const {
		for (size_t i = 0; i < _size; i++) {
			T* element = _data + i;
			if (condition(*element))
				return *element;
		}
		return nullptr;
	}
	size_t findIndex(const std::function<bool(const T&)>& condition) const {
		for (size_t i = 0; i < _size; i++)
			if (condition(*(_data + i)))
				return i;
		return nullptr;
	}

	T operator[](size_t index) const {
		return *(_data + index);
	}
	T& operator[](size_t index) {
		return *(_data + index);
	}
};

