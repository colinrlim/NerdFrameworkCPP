#include "Vector2.h"
#include "Math.h"

Vector2::Vector2(double x, double y) : x(x), y(y) { }
Vector2::Vector2(double s) : x(s), y(s) { };
Vector2::Vector2(const Vector2& a, const Vector2& b) : x(b.x - a.x), y(b.y - a.y) { }
Vector2::Vector2(const Vector2i& ivec) : x(ivec.x), y(ivec.y) { }
Vector2::Vector2(const Vector3& threedim) : x(threedim.x), y(threedim.y) { }
Vector2::Vector2(uint16_t integer) : x(((uint8_t*)&integer)[1] > 127 ? 256 - ((uint8_t*)&integer)[1] : ((uint8_t*)&integer)[1] * -1), y(((uint8_t*)&integer)[0] > 127 ? ((uint8_t*)&integer)[0] - 256 : ((uint8_t*)&integer)[0]) { }

const Vector2 Vector2::zero(0.0, 0.0);
const Vector2 Vector2::one(1.0, 1.0);

void Vector2::rotate(double radians) {

	/* x' = xcos(theta) - ysin(theta)
	 * y' = xsin(theta) + ycos(theta)
	 */
	
	const double s = Math::sin(radians);
	const double c = Math::cos(radians);
	
	const double newX = x * c - y * s;
	const double newY = x * s + y * c;
	x = newX;
	y = newY;
}
Vector2 Vector2::rotated(double radians) const {
	Vector2 newVec(*this);
	newVec.rotate(radians);
	return newVec;
}

template <typename iter>
void Vector2::rotate(iter begin, iter end, double radians) {
	const double s = Math::sin(radians);
	const double c = Math::cos(radians);

	while (begin != end) {
		Vector2& vec = *begin;
		const double newX = vec.x * c - vec.y * s;
		const double newY = vec.x * s + vec.y * c;
		vec.x = newX;
		vec.y = newY;
		++begin;
	}
}
template <typename iter, typename d_iter>
void Vector2::rotated(iter begin, iter end, d_iter dest, double radians) {
	const double s = Math::sin(radians);
	const double c = Math::cos(radians);

	while (begin != end) {
		const Vector2& vec = *begin;
		Vector2& destVec = *dest;
		destVec.x = vec.x * c - vec.y * s;
		destVec.y = vec.x * s + vec.y * c;
		++begin;
		++dest;
	}
}

double Vector2::magnitude() const {
	return Math::sqrt(this->x * this->x + this->y * this->y);
}
Vector2 Vector2::normalized() const {
	return *this / this->magnitude();
}
uint16_t Vector2::toInteger() const {
	uint16_t newInt;
	uint8_t* address = (uint8_t*)&newInt;
	address[1] = (uint8_t)((int)(x > 0 ? 256 - x : -1 * x));
	address[0] = (uint8_t)((int)(y >= 0 ? y : 256 + y));
	return newInt;
}
void Vector2::toInteger(uint16_t& integer) const {
	uint8_t* address = (uint8_t*)&integer;
	address[1] = (uint8_t)((int)(x > 0 ? 256 - x : -1 * x));
	address[0] = (uint8_t)((int)(y >= 0 ? y : 256 + y));
}
double Vector2::dot(const Vector2& a, const Vector2& b) {

    /* a⋅b = (a1*b1) + (a2*b2) + (a3*b3)
     *
     * a⋅b = 0 <=> a ⊥ b
     *
     * a⋅b = 1 <=> a'⋅b = 0 <=> a' ⊥ b
     *
     * a⋅b = |a||b|cos(theta)
     *
     * a⋅b = b⋅a
     */

    return (a.x * b.x) + (a.y * b.y);
}
Vector2 Vector2::lerp(const Vector2& a, const Vector2& b, double alpha) {
	return a * (1 - alpha) + b * alpha;
}
Vector2 Vector2::fromParameterization3(double t, double s, const Vector2& a, const Vector2& b, const Vector2& c) {
	double u = 1.0 - t - s;
	Vector2 newVec(a.x * u + b.x * t + c.x * s, a.y * u + b.y * t + c.y * s);
	return newVec;
}
Vector2 Vector2::fromRandom(const Vector2& min, const Vector2& max) {
	return Vector2(Math::random(min.x, max.x), Math::random(min.y, max.y));
}

Vector2& Vector2::operator+=(const Vector2& rhs) {
	this->x += rhs.x;
	this->y += rhs.y;
	return *this;
}
Vector2& Vector2::operator+=(double rhs) {
	this->x += rhs;
	this->y += rhs;
	return *this;
}
Vector2 Vector2::operator+(const Vector2& rhs) const {
	Vector2 newVec(this->x + rhs.x, this->y + rhs.y);
	return newVec;
}
Vector2 Vector2::operator+(double rhs) const {
	Vector2 newVec(this->x + rhs, this->y + rhs);
	return newVec;
}
Vector2& Vector2::operator-=(const Vector2& rhs) {
	this->x -= rhs.x;
	this->y -= rhs.y;
	return *this;
}
Vector2& Vector2::operator-=(double rhs) {
	this->x -= rhs;
	this->y -= rhs;
	return *this;
}
Vector2 Vector2::operator-(const Vector2& rhs) const {
	Vector2 newVec(this->x - rhs.x, this->y - rhs.y);
	return newVec;
}
Vector2 Vector2::operator-(double rhs) const {
	Vector2 newVec(this->x - rhs, this->y - rhs);
	return newVec;
}
Vector2 Vector2::operator-() const {
	Vector2 newVec(-this->x, -this->y);
	return newVec;
}
Vector2& Vector2::operator*=(const Vector2& rhs) {
	this->x *= rhs.x;
	this->y *= rhs.y;
	return *this;
}
Vector2& Vector2::operator*=(double rhs) {
	this->x *= rhs;
	this->y *= rhs;
	return *this;
}
Vector2 Vector2::operator*(const Vector2& rhs) const {
	Vector2 newVec(this->x * rhs.x, this->y * rhs.y);
	return newVec;
}
Vector2 Vector2::operator*(double rhs) const {
	Vector2 newVec(this->x * rhs, this->y * rhs);
	return newVec;
}
Vector2& Vector2::operator/=(const Vector2& rhs) {
	this->x /= rhs.x;
	this->y /= rhs.y;
	return *this;
}
Vector2& Vector2::operator/=(double rhs) {
	this->x /= rhs;
	this->y /= rhs;
	return *this;
}
Vector2 Vector2::operator/(const Vector2& rhs) const {
	Vector2 newVec(this->x / rhs.x, this->y / rhs.y);
	return newVec;
}
Vector2 Vector2::operator/(double rhs) const {
	Vector2 newVec(this->x / rhs, this->y / rhs);
	return newVec;
}

bool Vector2::operator==(const Vector2& rhs) const {
	return (*this - rhs).magnitude() <= 0.00001;
}
bool Vector2::operator!=(const Vector2& rhs) const {
	return (*this - rhs).magnitude() > 0.00001;
}

std::ostream& operator<<(std::ostream& stream, const Vector2& rhs) {
	return stream << "{ " << rhs.x << ", " << rhs.y << " }";
}