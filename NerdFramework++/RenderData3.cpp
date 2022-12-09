#include "RenderData3.h"

RenderData3::RenderData3() :
	textureU(0.0, 0.0),
	textureV(0.0, 1.0),
	textureW(1.0, 1.0),
	normalA(Vector3::zero),
	normalB(Vector3::zero),
	normalC(Vector3::zero),
	normalType(NormalType::DEFAULT),
	material(nullptr)
{ }
RenderData3::RenderData3(const Vector2& textureU, const Vector2& textureV, const Vector2& textureW, const Vector3& normalA, const Vector3& normalB, const Vector3& normalC, NormalType normalType, Material* material) :
	textureU(textureU),
	textureV(textureV),
	textureW(textureW),
	normalA(normalA),
	normalB(normalB),
	normalC(normalC),
	normalType(normalType),
	material(material)
{ }

void RenderData3::rotateX(double radians) {
	normalA = normalA.rotatedX(radians);
	normalB = normalB.rotatedX(radians);
	normalC = normalC.rotatedX(radians);
}
void RenderData3::rotateY(double radians) {
	normalA = normalA.rotatedY(radians);
	normalB = normalB.rotatedY(radians);
	normalC = normalC.rotatedY(radians);
}
void RenderData3::rotateZ(double radians) {
	normalA = normalA.rotatedZ(radians);
	normalB = normalB.rotatedZ(radians);
	normalC = normalC.rotatedZ(radians);
}
void RenderData3::rotate(double r1, double r2, double r3) {
	normalA = normalA.rotated(r1, r2, r3);
	normalB = normalB.rotated(r1, r2, r3);
	normalC = normalC.rotated(r1, r2, r3);
}

Vector2 RenderData3::textureCoordsAt(double t, double s) {
	return textureU * (1.0 - t - s) + textureV * t + textureW * s;
}
Vector3 RenderData3::normalAt(double t, double s) {
	return normalA * (1.0 - t - s) + normalB * t + normalC * s;
}