#pragma once

#include "BoundingShape3.h"

struct Sphere3 : BoundingShape3
{
	double r;

	Sphere3(Vector3& position, double radius);

	bool meets(const Vector3& point) const;
	bool meets(const Box3& box) const;
	bool meets(const Sphere3& sphere) const;
};

