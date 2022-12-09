#include "Box3.h"

Box3::Box3(Vector3& position, Vector3& size) : BoundingShape3(position), s(size) { }

bool Box3::meets(const Vector3& point) const {
	return (point.x >= p.x && point.y >= p.y && point.x <= p.x + s.x && point.y <= p.y + s.y);
}
bool Box3::meets(const Box3& box) const {
	return Box3::meets(box.p) || Box3::meets(box.p + box.s);
}
bool Box3::meets(const Sphere3& sphere) const {
	throw "Not implemented";
}