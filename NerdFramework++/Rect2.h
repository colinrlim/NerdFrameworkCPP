#pragma once

#include "Vector2i.h"
#include "Vector2.h"
#include "UDim2.h"

template <typename T>
struct Rect2
{
    T x;
    T y;
    T width;
    T height;
	Rect2(T x, T y, T width, T height) :
		x(x),
		y(y),
		width(width),
		height(height)
	{ }
	Rect2(const UDim2& position, const UDim2& size, int width, int height) :
		x((T)position.x.absolute(width)),
		y((T)position.y.absolute(height)),
		width((T)size.x.absolute(width)),
		height((T)size.y.absolute(height))
	{ }
	Rect2(const UDim2& position, const UDim2& size, const Rect2<double>& scope) :
		x((T)position.x.absolute(scope.width)),
		y((T)position.y.absolute(scope.height)),
		width((T)size.x.absolute(scope.width)),
		height((T)size.y.absolute(scope.height))
	{ }

	bool overlaps(const Vector2& point) const {
		return (point.x >= x && point.y >= y && point.x <= x + width && point.y <= y + height);
	}
	bool overlaps(const Vector2i& point) const {
		return (point.x >= x && point.y >= y && point.x <= x + width && point.y <= y + height);
	}
	bool overlaps(const Rect2<T>& rectangle) const {
		return this->overlaps(Vector2i(rectangle.x, rectangle.y)) || this->overlaps(Vector2i(rectangle.x + rectangle.width, rectangle.y + rectangle.height));
	}
};

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Rect2<T>& rhs) {
	return stream << "{ x: " << rhs.x << ", y: " << rhs.y << ", width: " << rhs.width << ", height: " << rhs.height << " }";
}

