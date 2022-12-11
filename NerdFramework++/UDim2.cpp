#include "UDim2.h"

UDim2::UDim2() : x(UDim()), y(UDim()) { }
UDim2::UDim2(double xScale, double xOffset, double yScale, double yOffset) :
	x(xScale, xOffset),
	y(yScale, yOffset)
{ }
UDim2::UDim2(double xOffset, double yOffset) :
	x(0.0, xOffset),
	y(0.0, yOffset)
{ }
UDim2::UDim2(const UDim& x, const UDim& y) : x(x), y(y) {}

const UDim2 UDim2::zero(UDim(0.0, 0.0), UDim(0.0, 0.0));
const UDim2 UDim2::one(UDim(1.0, 0.0), UDim(1.0, 0.0));

UDim2 UDim2::fromScale(double xScale, double yScale) {
	return UDim2(UDim(xScale, 0.0), UDim(yScale, 0.0));
}
UDim2 UDim2::fromOffset(double xOffset, double yOffset) {
	return UDim2(UDim(0.0, xOffset), UDim(0.0, yOffset));
}

Vector2 UDim2::absolute(double width, double height) const {
	return Vector2(x.absolute(width), y.absolute(height));
}

std::ostream& operator<<(std::ostream& stream, const UDim2& rhs) {
	return stream << "{ x: " << rhs.x << ", y: " << rhs.y << " }";
}