#include "Sphere3.h"
#include "Math.h"

Sphere3::Sphere3(Vector3& position, double radius) : BoundingShape3(position), r(radius) { }

bool Sphere3::meets(const Vector3& point) const {
	return (point - p).magnitude() <= r;
}
bool Sphere3::meets(const Box3& box) const {
	throw "Not implemented";
}
bool Sphere3::meets(const Sphere3& sphere) const {
	return (sphere.p - p).magnitude() <= Math::max(r, sphere.r);
}