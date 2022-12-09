#pragma once

#include "RenderData3.h"

struct RenderData4 : public RenderData3
{
    Vector2 textureX;

    Vector3 normalD;

    RenderData4();
    RenderData4(const Vector2& textureU, const Vector2& textureV, const Vector2& textureW, const Vector2& textureX, const Vector3& normalA, const Vector3& normalB, const Vector3& normalC, const Vector3& normalD, NormalType normalType = NormalType::INTERPOLATED, Material* material = nullptr);

    void rotateX(double radians);
    void rotateY(double radians);
    void rotateZ(double radians);
    void rotate(double r1, double r2, double r3);

    Vector2 textureCoordsAt(double t, double s);
    Vector3 normalAt(double t, double s);
};

