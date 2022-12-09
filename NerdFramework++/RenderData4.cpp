#include "RenderData4.h"

RenderData4::RenderData4() :
	RenderData3(),
	textureX(1.0, 0.0),
	normalD(Vector3::zero)
{ }
RenderData4::RenderData4(const Vector2& textureU, const Vector2& textureV, const Vector2& textureW, const Vector2& textureX, const Vector3& normalA, const Vector3& normalB, const Vector3& normalC, const Vector3& normalD, NormalType normalType, Material* material) :
	RenderData3(textureU, textureV, textureW, normalA, normalB, normalC, normalType, material),
	textureX(textureX),
	normalD(normalD)
{ }

void RenderData4::rotateX(double radians) {
	RenderData3::rotateX(radians);
	normalD = normalD.rotatedX(radians);
}
void RenderData4::rotateY(double radians) {
	RenderData3::rotateY(radians);
	normalD = normalD.rotatedY(radians);
}
void RenderData4::rotateZ(double radians) {
	RenderData3::rotateZ(radians);
	normalD = normalD.rotatedZ(radians);
}
void RenderData4::rotate(double r1, double r2, double r3) {
	RenderData3::rotate(r1, r2, r3);
	normalD = normalD.rotated(r1, r2, r3);
}

Vector2 RenderData4::textureCoordsAt(double t, double s) {
	return Vector2::lerp(Vector2::lerp(textureU, textureV, t), Vector2::lerp(textureX, textureW, t), s);
}
Vector3 RenderData4::normalAt(double t, double s) {
	return Vector3::lerp(Vector3::lerp(normalA, normalB, t), Vector3::lerp(normalD, normalC, t), s);
}