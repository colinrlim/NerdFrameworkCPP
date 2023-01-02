#pragma once

#include "Vector3s.h"
#include "Vector2.h"
struct Vector3s;
struct Vector2;

struct Vector3
{
	double x;
	double y;
	double z;

	Vector3(double x = 0.0, double y = 0.0, double z = 0.0);
	Vector3(double s);
	Vector3(const Vector3& a, const Vector3& b);
	Vector3(const Vector3s& spherical);
	Vector3(const Vector2& twodim);

	Vector3s asSpherical() const;

	static const Vector3 zero;
	static const Vector3 one;
	static const Vector3 xAxis;
	static const Vector3 yAxis;
	static const Vector3 zAxis;

	double magnitude() const;
	Vector3 normalized() const;
	Vector3 normalizedCubic() const;

	void rotateX(double radians);
	void rotateY(double radians);
	void rotateZ(double radians);
	void rotate(double r1, double r2, double r3);
	void rotateAbout(const Vector3& rotand, double radians);

	Vector3 rotatedX(double radians) const;
	Vector3 rotatedY(double radians) const;
	Vector3 rotatedZ(double radians) const;
	Vector3 rotated(double r1, double r2, double r3) const;
	Vector3 rotatedAbout(const Vector3& rotand, double radians) const;

	template <typename iter>
	static void rotateX(iter begin, iter end, double radians);
	template <typename iter>
	static void rotateY(iter begin, iter end, double radians);
	template <typename iter>
	static void rotateZ(iter begin, iter end, double radians);
	template <typename iter>
	static void rotate(iter begin, iter end, double r1, double r2, double r3);

	template <typename iter, typename d_iter>
	static void rotatedX(iter begin, iter end, d_iter dest, double radians);
	template <typename iter, typename d_iter>
	static void rotatedY(iter begin, iter end, d_iter dest, double radians);
	template <typename iter, typename d_iter>
	static void rotatedZ(iter begin, iter end, d_iter dest, double radians);
	template <typename iter, typename d_iter>
	static void rotated(iter begin, iter end, d_iter dest, double r1, double r2, double r3);

	static Vector3 angle3(const Vector3& a, const Vector3& b);
	static double angle(const Vector3& a, const Vector3& b);
	static double dot(const Vector3& a, const Vector3& b);
	static Vector3 cross(const Vector3& a, const Vector3& b);
	static double triple(const Vector3& a, const Vector3& b, const Vector3& c);
	static bool parallel(const Vector3& a, const Vector3& b);
	static Vector3 lerp(const Vector3& a, const Vector3& b, double alpha);
	static Vector3 fromParameterization3(double t, double s, const Vector3& a, const Vector3& b, const Vector3& c);
	static Vector3 fromRandom(const Vector3& min, const Vector3& max);

	Vector3& operator+=(const Vector3& rhs);
	Vector3& operator+=(double rhs);
	Vector3 operator+(const Vector3& rhs) const;
	Vector3 operator+(double rhs) const;
	Vector3& operator-=(const Vector3& rhs);
	Vector3& operator-=(double rhs);
	Vector3 operator-(const Vector3& rhs) const;
	Vector3 operator-(double rhs) const;
	Vector3 operator-() const;
	Vector3& operator*=(const Vector3& rhs);
	Vector3& operator*=(double rhs);
	Vector3 operator*(const Vector3& rhs) const;
	Vector3 operator*(double rhs) const;
	Vector3& operator/=(const Vector3& rhs);
	Vector3& operator/=(double rhs);
	Vector3 operator/(const Vector3& rhs) const;
	Vector3 operator/(double rhs) const;

	bool operator==(const Vector3& rhs) const;
	bool operator!=(const Vector3& rhs) const;
};

std::ostream& operator<<(std::ostream& stream, const Vector3& rhs);

