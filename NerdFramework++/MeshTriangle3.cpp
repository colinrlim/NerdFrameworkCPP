#include "MeshTriangle3.h"

MeshTriangle3::MeshTriangle3(Vector3* a, Vector3* b, Vector3* c) :
	Triangle3(a, b, c),
	RenderData3(),
	PhysicsData3()
{ }
MeshTriangle3::MeshTriangle3(Vector3* a, Vector3* b, Vector3* c, const Vector2& textureU, const Vector2& textureV, const Vector2& textureW, const Vector3& normalA, const Vector3& normalB, const Vector3& normalC, RenderData3::NormalType normalType, Material* material) :
	Triangle3(a, b, c),
	RenderData3(textureU, textureV, textureW, normalA, normalB, normalC, normalType, material),
	PhysicsData3()
{ }

MeshTriangle3::MeshTriangle3(const MeshTriangle3& rhs) :
	Triangle3(&rhs.a, &rhs.b, &rhs.c),
	RenderData3(rhs.textureU, rhs.textureV, rhs.textureW, rhs.normalA, rhs.normalB, rhs.normalC, rhs.normalType, rhs.material),
	PhysicsData3()
{ }
MeshTriangle3::~MeshTriangle3() { }
MeshTriangle3& MeshTriangle3::operator=(const MeshTriangle3& rhs) { return *this; }

void MeshTriangle3::rotateX(double radians, const Vector3& origin) {
	Triangle3::rotateX(radians, origin);
	RenderData3::rotateX(radians);
}
void MeshTriangle3::rotateY(double radians, const Vector3& origin) {
	Triangle3::rotateY(radians, origin);
	RenderData3::rotateY(radians);
}
void MeshTriangle3::rotateZ(double radians, const Vector3& origin) {
	Triangle3::rotateZ(radians, origin);
	RenderData3::rotateZ(radians);
}
void MeshTriangle3::rotate(double r1, double r2, double r3, const Vector3& origin) {
	Triangle3::rotate(r1, r2, r3, origin);
	RenderData3::rotate(r1, r2, r3);
}