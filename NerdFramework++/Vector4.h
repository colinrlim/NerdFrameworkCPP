#pragma once

#include "Vector3.h"
struct Vector3;

struct Vector4 {
	double w;
	double x;
	double y;
	double z;

	Vector4(double w, double x, double y, double z);
	Vector4(Vector3 rhs);

	double shrinkageFactor() const;
	double magnitude() const;
	Vector4 normalized() const;

	Vector4& operator+=(const Vector4& rhs);
	Vector4 operator+(const Vector4& rhs) const;
	Vector4& operator-=(const Vector4& rhs);
	Vector4 operator-(const Vector4& rhs) const;
	Vector4 operator-() const;
	Vector4& operator*=(const Vector4& rhs);
	Vector4 operator*(const Vector4& rhs) const;
	Vector4& operator/=(const Vector4& rhs);
	Vector4 operator/(const Vector4& rhs) const;
	bool operator==(const Vector4& rhs) const;
	bool operator!=(const Vector4& rhs) const;
};

