#pragma once

#include "Material.h"

struct RenderData3
{
    enum class NormalType {
        DEFAULT,
        INTERPOLATED
    };

    Vector2 textureU;
    Vector2 textureV;
    Vector2 textureW;

    Vector3 normalA;
    Vector3 normalB;
    Vector3 normalC;

    NormalType normalType;
    Material* material;

    RenderData3();
    RenderData3(const Vector2& textureU, const Vector2& textureV, const Vector2& textureW, const Vector3& normalA, const Vector3& normalB, const Vector3& normalC, RenderData3::NormalType normalType = RenderData3::NormalType::INTERPOLATED, Material* material = nullptr);

    void rotateX(double radians);
    void rotateY(double radians);
    void rotateZ(double radians);
    void rotate(double r1, double r2, double r3);   

    Vector2 textureCoordsAt(double t, double s);
    Vector3 normalAt(double t, double s);
};

