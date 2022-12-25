#include "Vector2.h"
#include "Math.h"

Vector2::Vector2(double x, double y) : x(x), y(y) { }
Vector2::Vector2(double s) : x(s), y(s) { };
Vector2::Vector2(const Vector2& a, const Vector2& b) : x(b.x - a.x), y(b.y - a.y) { }
Vector2::Vector2(const Vector3& threedim) : x(threedim.x), y(threedim.y) { }
Vector2::Vector2(uint16_t integer) : x(((uint8_t*)&integer)[1]), y(((uint8_t*)&integer)[2]) { }

const Vector2 Vector2::zero(0.0, 0.0);
const Vector2 Vector2::one(1.0, 1.0);

double Vector2::magnitude() {
	return Math::sqrt(this->x * this->x + this->y * this->y);
}
Vector2 Vector2::normalized() {
	return *this / this->magnitude();
}
uint16_t Vector2::toInteger() {
	uint16_t newInt;
	uint8_t* address = (uint8_t*)&newInt;
	address[1] = (uint8_t)x;
	address[0] = (uint8_t)y;
	return newInt;
}
void Vector2::toInteger(uint16_t& integer) {
	uint8_t* address = (uint8_t*)&integer;
	address[1] = (uint8_t)x;
	address[0] = (uint8_t)y;
}
Vector2 Vector2::lerp(const Vector2& a, const Vector2& b, double alpha) {
	return a * (1 - alpha) + b * alpha;
}
Vector2 Vector2::fromParameterization3(double t, double s, const Vector2& a, const Vector2& b, const Vector2& c) {
	double u = 1.0 - t - s;
	Vector2 newVec(a.x * u + b.x * t + c.x * s, a.y * u + b.y * t + c.y * s);
	return newVec;
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