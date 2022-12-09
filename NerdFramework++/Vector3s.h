#pragma once

#include "Vector3.h"
struct Vector3;

struct Vector3s
{
	// Radius
	double rho;
	// Zenith angle
	double phi;
	// Polar angle
	double theta;

	Vector3s(double rho = 1.0, double phi = 0.0, double theta = 0.0);
	Vector3s(const Vector3& rectangular);

	Vector3 asRectangular() const;

	Vector3s rotatedZenith(double radians) const;
	Vector3s rotatedPolar(double radians) const;

	static Vector3s min(const Vector3s& a, const Vector3s& b);
};

