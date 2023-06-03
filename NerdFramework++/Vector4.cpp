#include "Vector4.h"
#include "Math.h"

Vector4::Vector4(double w, double x, double y, double z) :
	w(w),
	x(x),
	y(y),
	z(z)
{ }
Vector4::Vector4(Vector3 rhs) :
	w(0.0),
	x(rhs.x),
	y(rhs.y),
	z(rhs.z)
{ }

double Vector4::shrinkageFactor() const {
	return 1.0 - 1.0 / (w * w + x * x + y * y + z * z);
}
double Vector4::magnitude() const {
	return Math::sqrt(w*w + x*x + y*y + z*z);
}
Vector4 Vector4::normalized() const {
	const double length = magnitude();
	return Vector4(w / length, x / length, y / length, z / length);
}

Vector4& Vector4::operator+=(const Vector4& rhs) {
	w += rhs.w;
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}
Vector4 Vector4::operator+(const Vector4& rhs) const {
	return Vector4(w + rhs.w, x + rhs.x, y + rhs.y, z + rhs.z);
}
Vector4& Vector4::operator-=(const Vector4& rhs) {
	w -= rhs.w;
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}
Vector4 Vector4::operator-(const Vector4& rhs) const {
	return Vector4(w - rhs.w, x - rhs.x, y - rhs.y, z - rhs.z);
}
Vector4 Vector4::operator-() const {
	return Vector4(-w, -x, -y, -z);
}
Vector4& Vector4::operator*=(const Vector4& rhs) {
	*this = *this * rhs;
	return *this;
}
Vector4 Vector4::operator*(const Vector4& rhs) const {
	return Vector4(
		w*rhs.w - x*rhs.x - y*rhs.y - z*rhs.z,
		w*rhs.x + x*rhs.w + y*rhs.z - z*rhs.y,
		w*rhs.y - x*rhs.z + y*rhs.w + z*rhs.x,
		w*rhs.z + x*rhs.y - y*rhs.x + z*rhs.w
	);
}
Vector4& Vector4::operator/=(const Vector4& rhs) {
	*this = *this / rhs;
	return *this;
}
Vector4 Vector4::operator/(const Vector4& rhs) const {
	return Vector4(
		-w * rhs.w + x * rhs.x + y * rhs.y + z * rhs.z,
		-w * rhs.x - x * rhs.w - y * rhs.z + z * rhs.y,
		-w * rhs.y + x * rhs.z - y * rhs.w - z * rhs.x,
		-w * rhs.z - x * rhs.y + y * rhs.x - z * rhs.w
	);
}
bool Vector4::operator==(const Vector4& rhs) const {
	return abs(w - rhs.w) <= 0.00001 &&
		   abs(x - rhs.x) <= 0.00001 &&
		   abs(y - rhs.y) <= 0.00001 &&
		   abs(z - rhs.z) <= 0.00001;
}
bool Vector4::operator!=(const Vector4& rhs) const {
	return abs(w - rhs.w) > 0.00001 &&
		   abs(x - rhs.x) > 0.00001 &&
		   abs(y - rhs.y) > 0.00001 &&
		   abs(z - rhs.z) > 0.00001;
}