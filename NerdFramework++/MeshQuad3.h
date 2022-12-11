#pragma once

#include "MeshTriangle3.h"
#include "PhysicsData4.h"
#include "RenderData4.h"
#include "Quad3.h"

class MeshQuad3 : public Quad3, public RenderData4, public PhysicsData4
{
private:
	MeshQuad3(Vector3* a, Vector3* b, Vector3* c, Vector3* d);
	MeshQuad3(Vector3* a, Vector3* b, Vector3* c, Vector3* d, const Vector2& textureU, const Vector2& textureV, const Vector2& textureW, const Vector2& textureX, const Vector3& normalA, const Vector3& normalB, const Vector3& normalC, const Vector3& normalD, RenderData3::NormalType normalType = RenderData3::NormalType::INTERPOLATED, Material* material = nullptr);

	friend class MeshParser;
public:
	MeshTriangle3* getMeshTriangle1() const;
	MeshTriangle3* getMeshTriangle2() const;
};

