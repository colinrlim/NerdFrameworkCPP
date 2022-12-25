#include "Vector2i.h"
#include "Math.h"

Vector2i::Vector2i(int x, int y) : x(x), y(y) { }
Vector2i::Vector2i(int s) : x(s), y(s) { };
Vector2i::Vector2i(const Vector2i& a, const Vector2i& b) : x(b.x - a.x), y(b.y - a.y) { }
Vector2i::Vector2i(const Vector3& threedim) : x((int)threedim.x), y((int)threedim.y) { }
Vector2i::Vector2i(uint16_t integer) : x(((uint8_t*)&integer)[1]), y(((uint8_t*)&integer)[2]) { }

const Vector2i Vector2i::zero(0, 0);
const Vector2i Vector2i::one(1, 1);

double Vector2i::magnitude() {
	return Math::sqrt(this->x * this->x + this->y * this->y);
}
Vector2i Vector2i::normalized() {
	return *this / (int)this->magnitude();
}
uint16_t Vector2i::toInteger() {
	uint16_t newInt;
	uint8_t* address = (uint8_t*)&newInt;
	address[1] = (uint8_t)x;
	address[0] = (uint8_t)y;
	return newInt;
}
void Vector2i::toInteger(uint16_t& integer) {
	uint8_t* address = (uint8_t*)&integer;
	address[1] = (uint8_t)x;
	address[0] = (uint8_t)y;
}
Vector2i Vector2i::fromParameterization3(double t, double s, const Vector2i& a, const Vector2i& b, const Vector2i& c) {
	double u = 1.0 - t - s;
	Vector2i newVec((int)(a.x * u + b.x * t + c.x * s), (int)(a.y * u + b.y * t + c.y * s));
	return newVec;
}

Vector2i& Vector2i::operator+=(const Vector2i& rhs) {
	this->x += rhs.x;
	this->y += rhs.y;
	return *this;
}
Vector2i& Vector2i::operator+=(int rhs) {
	this->x += rhs;
	this->y += rhs;
	return *this;
}
Vector2i Vector2i::operator+(const Vector2i& rhs) const {
	Vector2i newVec(this->x + rhs.x, this->y + rhs.y);
	return newVec;
}
Vector2i Vector2i::operator+(int rhs) const {
	Vector2i newVec(this->x + rhs, this->y + rhs);
	return newVec;
}
Vector2i& Vector2i::operator-=(const Vector2i& rhs) {
	this->x -= rhs.x;
	this->y -= rhs.y;
	return *this;
}
Vector2i& Vector2i::operator-=(int rhs) {
	this->x -= rhs;
	this->y -= rhs;
	return *this;
}
Vector2i Vector2i::operator-(const Vector2i& rhs) const {
	Vector2i newVec(this->x - rhs.x, this->y - rhs.y);
	return newVec;
}
Vector2i Vector2i::operator-(int rhs) const {
	Vector2i newVec(this->x - rhs, this->y - rhs);
	return newVec;
}
Vector2i Vector2i::operator-() const {
	Vector2i newVec(-this->x, -this->y);
	return newVec;
}
Vector2i& Vector2i::operator*=(const Vector2i& rhs) {
	this->x *= rhs.x;
	this->y *= rhs.y;
	return *this;
}
Vector2i& Vector2i::operator*=(int rhs) {
	this->x *= rhs;
	this->y *= rhs;
	return *this;
}
Vector2i Vector2i::operator*(const Vector2i& rhs) const {
	Vector2i newVec(this->x * rhs.x, this->y * rhs.y);
	return newVec;
}
Vector2i Vector2i::operator*(int rhs) const {
	Vector2i newVec(this->x * rhs, this->y * rhs);
	return newVec;
}
Vector2i& Vector2i::operator/=(const Vector2i& rhs) {
	this->x /= rhs.x;
	this->y /= rhs.y;
	return *this;
}
Vector2i& Vector2i::operator/=(int rhs) {
	this->x /= rhs;
	this->y /= rhs;
	return *this;
}
Vector2i Vector2i::operator/(const Vector2i& rhs) const {
	Vector2i newVec(this->x / rhs.x, this->y / rhs.y);
	return newVec;
}
Vector2i Vector2i::operator/(int rhs) const {
	Vector2i newVec(this->x / rhs, this->y / rhs);
	return newVec;
}

bool Vector2i::operator==(const Vector2i& rhs) const {
	return (*this - rhs).magnitude() == 0;
}
bool Vector2i::operator!=(const Vector2i& rhs) const {
	return (*this - rhs).magnitude() > 0;
}

std::ostream& operator<<(std::ostream& stream, const Vector2i& rhs) {
	return stream << "{ " << rhs.x << ", " << rhs.y << " }";
}