#pragma once

#include "BoundingShape3.h"

struct Box3 : BoundingShape3
{
    Vector3& s;

    Box3(Vector3& position, Vector3& size);

	bool meets(const Vector3& point) const;
	bool meets(const Box3& box) const;
	bool meets(const Sphere3& sphere) const;
};

