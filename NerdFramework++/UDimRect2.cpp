#include "UDimRect2.h"

UDimRect2::UDimRect2(const UDim2& position, const UDim2& size) : p(position), s(size) { }
UDimRect2::UDimRect2(const Vector2& position, const Vector2& size) :
	p(0.0, position.x, 0.0, position.y),
	s(0.0, size.x, 0.0, size.y)
{ }

const UDimRect2 UDimRect2::one(Vector2::zero, Vector2::one);

bool UDimRect2::overlaps(const Vector2& point, int windowWidth, int windowHeight) const {
    Vector2 pAbsolute = p.absolute(windowWidth, windowHeight);
    Vector2 sAbsolute = s.absolute(windowWidth, windowHeight);
    return (point.x >= pAbsolute.x && point.y >= pAbsolute.y && point.x <= pAbsolute.x + sAbsolute.x && point.y <= pAbsolute.y + sAbsolute.y);
}
bool UDimRect2::overlaps(const UDimRect2& rectangle, int windowWidth, int windowHeight) const {
    Vector2 pAbsolute = rectangle.p.absolute(windowWidth, windowHeight);
    Vector2 sAbsolute = rectangle.s.absolute(windowWidth, windowHeight);
    return this->overlaps(pAbsolute) || this->overlaps(pAbsolute + sAbsolute);
}

std::ostream& operator<<(std::ostream& stream, const UDimRect2& rhs) {
    return stream << "{ p: " << rhs.p << ", s: " << rhs.s << " }";
}