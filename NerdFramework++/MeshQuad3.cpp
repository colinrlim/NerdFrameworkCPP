#include "MeshQuad3.h"

MeshQuad3::MeshQuad3(Vector3* a, Vector3* b, Vector3* c, Vector3* d) :
    Quad3(a, b, c, d),
    RenderData4(),
    PhysicsData4()
{
    /* A ----- D
     * |       |
     * |       |
     * |       |
     * B ----- C
     *
     * Normal points out of the page
     */
}
MeshQuad3::MeshQuad3(Vector3* a, Vector3* b, Vector3* c, Vector3* d, const Vector2& textureU, const Vector2& textureV, const Vector2& textureW, const Vector2& textureX, const Vector3& normalA, const Vector3& normalB, const Vector3& normalC, const Vector3& normalD, RenderData3::NormalType normalType, Material* material) :
    Quad3(a, b, c, d),
    RenderData4(textureU, textureV, textureW, textureX, normalA, normalB, normalC, normalD, normalType, material),
    PhysicsData4()
{ }

MeshTriangle3* MeshQuad3::meshTriangle1() const {
    return new MeshTriangle3(&a, &b, &c, textureU, textureV, textureW, normalA, normalB, normalC, normalType, material);
}
MeshTriangle3* MeshQuad3::meshTriangle2() const {
    return new MeshTriangle3(&a, &c, &d, textureU, textureW, textureX, normalA, normalC, normalD, normalType, material);
}