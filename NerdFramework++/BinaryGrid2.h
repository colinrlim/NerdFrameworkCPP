#pragma once

#include <cstdint>

struct BinaryGrid2 {
private:
	size_t _width;
	size_t _height;
	uint8_t* _data;
public:
	BinaryGrid2(size_t width, size_t height);
	BinaryGrid2(size_t width, size_t height, bool value);
	BinaryGrid2(const BinaryGrid2& rhs);
	BinaryGrid2& operator=(const BinaryGrid2& rhs);
	~BinaryGrid2();

	size_t getWidth() const;
	size_t getHeight() const;

	uint8_t* data() const;
	size_t size() const;

	bool getTile(size_t x, size_t y) const;
	void setTile(size_t x, size_t y, bool value);
};

