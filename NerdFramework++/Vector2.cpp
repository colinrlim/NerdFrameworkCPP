#include "Vector2.h"
#include "Math.h"

Vector2::Vector2(double x, double y) : x(x), y(y) { }
Vector2::Vector2(double s) : x(s), y(s) { };
Vector2::Vector2(const Vector2& a, const Vector2& b) : x(b.x - a.x), y(b.y - a.y) { }
Vector2::Vector2(const Vector3& threedim) : x(threedim.x), y(threedim.y) { }

const Vector2 Vector2::zero(0.0, 0.0);
const Vector2 Vector2::one(1.0, 1.0);

inline double Vector2::magnitude() {
	return Math::sqrt(this->x * this->x + this->y * this->y);
}
inline Vector2 Vector2::normalized() {
	return *this / this->magnitude();
}
inline Vector2 Vector2::lerp(const Vector2& a, const Vector2& b, double alpha) {
	return a * (1 - alpha) + b * alpha;
}
inline Vector2 Vector2::fromParameterization3(double t, double s, const Vector2& a, const Vector2& b, const Vector2& c) {
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