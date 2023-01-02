#include "Vector2i.h"
#include "Math.h"

Vector2i::Vector2i(int x, int y) : x(x), y(y) { }
Vector2i::Vector2i(int s) : x(s), y(s) { };
Vector2i::Vector2i(const Vector2i& a, const Vector2i& b) : x(b.x - a.x), y(b.y - a.y) { }
Vector2i::Vector2i(const Vector3& threedim) : x((int)threedim.x), y((int)threedim.y) { }
Vector2i::Vector2i(uint16_t integer) : x(((uint8_t*)&integer)[1] > 127 ? 256 - ((uint8_t*)&integer)[1] : ((uint8_t*)&integer)[1] * -1), y(((uint8_t*)&integer)[0] > 127 ? ((uint8_t*)&integer)[0] - 256 : ((uint8_t*)&integer)[0]) { }

const Vector2i Vector2i::zero(0, 0);
const Vector2i Vector2i::one(1, 1);

void Vector2i::rotate(double radians) {

	/* x' = xcos(theta) - ysin(theta)
	 * y' = xsin(theta) + ycos(theta)
	 */
	
	const double s = Math::sin(radians);
	const double c = Math::cos(radians);
	
	const double newX = x * c - y * s + 0.0001;
	const double newY = x * s + y * c + 0.0001;
	x = (int)x;
	y = (int)y;
}
Vector2i Vector2i::rotated(double radians) const {
	Vector2i newVec(*this);
	newVec.rotate(radians);
	return newVec;
}

template <typename iter>
static void Vector2i::rotate(iter begin, iter end, double radians) {
	const double s = Math::sin(radians);
	const double c = Math::cos(radians);

	while (begin != end) {
		Vector2i& vec = *begin;
		const double newX = vec.x * c - vec.y * s;
		const double newY = vec.x * s + vec.y * c;
		vec.x = (int)newX;
		vec.y = (int)newY;
		++begin;
		++dest;
	}
}
template <typename iter, typename d_iter>
static void Vector2i::rotated(iter begin, iter end, d_iter dest, double radians) {
	const double s = Math::sin(radians);
	const double c = Math::cos(radians);

	while (begin != end) {
		const Vector2i& vec = *begin;
		Vector2i& destVec = *dest;
		destVec.x = (int)(vec.x * c - vec.y * s);
		destVec.y = (int)(vec.x * s + vec.y * c);
		++begin;
		++dest;
	}
}

double Vector2i::magnitude() const {
	return Math::sqrt(this->x * this->x + this->y * this->y);
}
Vector2i Vector2i::normalized() const {
	return *this / (int)this->magnitude();
}
uint16_t Vector2i::toInteger() const {
	uint16_t newInt;
	uint8_t* address = (uint8_t*)&newInt;
	address[1] = (uint8_t)(x > 0 ? 256 - x : -1 * x);
	address[0] = (uint8_t)(y >= 0 ? y : 256 + y);
	return newInt;
}
void Vector2i::toInteger(uint16_t& integer) const {
	uint8_t* address = (uint8_t*)&integer;
	address[1] = (uint8_t)(x > 0 ? 256 - x : -1 * x);
	address[0] = (uint8_t)(y >= 0 ? y : 256 + y);
}
Vector2i Vector2i::fromParameterization3(double t, double s, const Vector2i& a, const Vector2i& b, const Vector2i& c) {
	double u = 1.0 - t - s;
	Vector2i newVec((int)(a.x * u + b.x * t + c.x * s), (int)(a.y * u + b.y * t + c.y * s));
	return newVec;
}
Vector2i Vector2i::fromRandom(const Vector2i& min, const Vector2i& max) {
	return Vector2i(Math::random(min.x, max.x), Math::random(min.y, max.y));
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