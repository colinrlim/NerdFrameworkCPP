#pragma once

#include "Vector3.h"
struct Box3;
struct Sphere3;

struct BoundingShape3 {
	Vector3& p;

	BoundingShape3(Vector3& position);

	virtual bool meets(const Vector3& point) const = 0;
	virtual bool meets(const Box3& box) const = 0;
	virtual bool meets(const Sphere3& sphere) const = 0;
};

