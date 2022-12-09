#pragma once

#include "PhysicsData3.h"
#include "RenderData3.h"
#include "Triangle3.h"

class MeshTriangle3 : public Triangle3, public RenderData3, public PhysicsData3
{
private:
    MeshTriangle3(Vector3* a, Vector3* b, Vector3* c);
    MeshTriangle3(Vector3* a, Vector3* b, Vector3* c, const Vector2& textureU, const Vector2& textureV, const Vector2& textureW, const Vector3& normalA, const Vector3& normalB, const Vector3& normalC, RenderData3::NormalType normalType = RenderData3::NormalType::INTERPOLATED, Material* material = nullptr);

    friend class Mesh;
    friend class MeshQuad3;
    friend class MeshParser;
public:
    MeshTriangle3(const MeshTriangle3& rhs);
    ~MeshTriangle3();
    MeshTriangle3& operator=(const MeshTriangle3& rhs);

    void rotateX(double radians, const Vector3& origin);
    void rotateY(double radians, const Vector3& origin);
    void rotateZ(double radians, const Vector3& origin);
    void rotate(double r1, double r2, double r3, const Vector3& origin);
};

