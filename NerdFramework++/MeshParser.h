#pragma once

#include <string>
#include "Mesh.h"

class MeshParser
{
public:
    static Mesh* fromMesh(const Mesh& mesh);
    static Mesh* fromFile(const char* filename, bool overrideNormalInterpolation = false, Material* material = nullptr);

    static Mesh* fromCube(const Vector3& origin, double sideLength);
    static Mesh* fromUVSphere(const Vector3& origin, double radius, int segments = 2, int rings = 4);
    static Mesh* fromIcoSphere(const Vector3& origin, double radius, int iterations = 2, RenderData3::NormalType normalType = RenderData3::NormalType::DEFAULT);
    static Mesh* fromQuadSphere(const Vector3& origin, double radius, int iterations = 2, RenderData3::NormalType normalType = RenderData3::NormalType::DEFAULT);

    static void destroyMesh(Mesh* mesh);
};

