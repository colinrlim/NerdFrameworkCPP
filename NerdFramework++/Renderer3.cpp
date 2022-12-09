#include "MaterialManager.h"
#include "Renderer3.h"
#include "Math.h"
#include <algorithm>
#include <iterator>

Color4 Renderer3::totalColorAt(const MeshTriangle3& triangle, const Color4& colorA, const Color4& colorB, const Color4& colorC, double t, double s) const {
    Vector2 textureCoords = Vector2::fromParameterization3(t, s, triangle.textureU, triangle.textureV, triangle.textureW);

    Material material = *triangle.material;
    Color4 textureLight = material.texture.colorAt(textureCoords.x, textureCoords.y);
    Color4 diffuseLight = Color4::fromVector3(material.diffuseColor);
    double lightValue = Color4::valueFromParameterization(t, s, colorA, colorB, colorC) / 255.0;

    Color4 flattened = Color4::flattened(diffuseLight, textureLight);
    //Color4.Lerp(Color4.Black, Color4.Flatten(diffuseLight, textureLight), lightValue).WithAlpha(material.alpha);
    return Color4(
        (uint8_t)(flattened.r * lightValue),
        (uint8_t)(flattened.g * lightValue),
        (uint8_t)(flattened.b * lightValue),
        (uint8_t)(((1.0 - lightValue / 255.0) + (flattened.alpha / 255.0 * lightValue / 255.0)) * material.alpha)
    );
}
Color4 Renderer3::calculateLighting(const Vector3& point, const Vector3& normal) const {
    return Color4::white;
    /*Vector3 displacement = cameraLight.rayCaster.d.p - point;
    double angle = Vector3::angle(normal, displacement);
    double distance = displacement.magnitude();
    return cameraLight.LightAt(distance, angle);*/
}
Color4 Renderer3::renderFog(const Color4& original, double distance) const {
    /* Uses alpha as intensity of fog per unit distance
     */

    return Color4::lerp(fog.opaque(), original, Math::pow(1.0 - fog.alpha, distance));
}
void Renderer3::processFaces(const Rect2<double>& scope) {
    _processedFaces.clear();
    std::copy_if(_meshFaces.begin(), _meshFaces.end(), std::back_inserter(_processedFaces), [this](const MeshTriangle3* triangle) -> bool { return camera.meets(*triangle); });
    std::sort(_processedFaces.begin(), _processedFaces.end(), [this](const MeshTriangle3* a, const MeshTriangle3* b) -> bool {
        return ((a->a + a->b + a->c) / 3.0 - camera.d.p).magnitude() < ((b->a + b->b + b->c) / 3.0 - camera.d.p).magnitude();
    });
    for (auto iterator = _points.begin(); iterator != _points.end(); ++iterator) {
        Vector3 point = *(*iterator);
        //if (!camera.meets(point)) continue;
        _pointProjections.insert_or_assign(*iterator, camera.projection(point) * Vector2(scope.width, scope.height));
        _pointDistances.insert_or_assign(*iterator, camera.distance(point));
    }
}

Renderer3::Renderer3(RayCaster& camera) :
    Renderer2(),
	camera(camera),
    fog(0, 0, 0, 1),
    depthBuffer(1, 1),
    normalBuffer(1, 1)
{
	onDraw = [this](UIObject& obj, Image4& screen, const Rect2<double>& scope) -> void {
		renderBatchRasterized(screen, scope);
	};
	onDrawSDL = [this](UIObject& obj, SDL_Renderer* renderer, const Rect2<double>& scope) -> void {
		renderBatchRasterized(renderer, scope);
	};
}
Renderer3::Renderer3(const UDim2& position, const UDim2& size, RayCaster& camera) :
    Renderer2(position, size),
    camera(camera),
    fog(0, 0, 0, 1),
    depthBuffer(1, 1),
    normalBuffer(1, 1)
{
	onDraw = [this](UIObject& obj, Image4& screen, const Rect2<double>& scope) -> void {
		renderBatchRasterized(screen, scope);
	};
	onDrawSDL = [this](UIObject& obj, SDL_Renderer* renderer, const Rect2<double>& scope) -> void {
		renderBatchRasterized(renderer, scope);
	};
}

void Renderer3::addMesh(Mesh* mesh) {
    for (auto iterator = mesh->faces.objects.begin(); iterator != mesh->faces.objects.end(); ++iterator) {
		_meshFaces.push_back(*iterator);
	}
    for (auto iterator = mesh->vertices.begin(); iterator != mesh->vertices.end(); ++iterator) {
        _points.push_back(*iterator);
    }
}
void Renderer3::removeMesh(const Mesh* mesh) {
	for (auto iterator = _meshFaces.begin(); iterator != _meshFaces.end(); ++iterator) {
		for (size_t x = 0; x < mesh->faces.objects.size(); x++) {
			if (*iterator == mesh->faces.objects[x])
				_meshFaces.erase(iterator);
		}
	}
    for (size_t x = 0; x < mesh->vertices.size(); x++) {
        Vector3* vertice = mesh->vertices[x];
        _pointProjections.erase(vertice);
        _pointDistances.erase(vertice);
        for (auto iterator = _points.begin(); iterator != _points.end(); ++iterator)
            if (*iterator == vertice)
                _points.erase(iterator);
    }
}

void Renderer3::renderBatchRasterized(Image4& screen, const Rect2<double>& scope, double minDist, double maxDist) {
    depthBuffer = Grid2<uint32_t>((size_t)scope.width, (size_t)scope.height, (uint32_t)UINT32_MAX);
    normalBuffer = Grid2<Vector3>((size_t)scope.width, (size_t)scope.height, Vector3::zero);
    processFaces(scope);
    for (auto iterator = _processedFaces.begin(); iterator != _processedFaces.end(); ++iterator)
    {

    }
}
void Renderer3::renderBatchRasterized(SDL_Renderer* renderer, const Rect2<double>& scope, double minDist, double maxDist) {
    processFaces(scope);
    for (auto iterator = _processedFaces.begin(); iterator != _processedFaces.end(); ++iterator)
    {
        const MeshTriangle3& triangle = *(*iterator);
        Vector2& a = _pointProjections[&triangle.a];
        Vector2& b = _pointProjections[&triangle.b];
        Vector2& c = _pointProjections[&triangle.c];

        if ((a.x < 0.0 && b.x < 0.0 && c.x < 0.0) ||
            (a.y < 0.0 && b.y < 0.0 && c.y < 0.0) ||
            (a.x > scope.width && b.x > scope.width && c.x > scope.width) ||
            (a.y > scope.height && b.y > scope.height && c.y > scope.height)) return;

        double distance1 = _pointDistances[&triangle.a];
        double distance2 = _pointDistances[&triangle.b];
        double distance3 = _pointDistances[&triangle.c];

        double avgDist = Math::average(std::vector<double>{ distance1, distance2, distance3 });
        if (avgDist < minDist || avgDist > maxDist) return;

        if (triangle.normalType == RenderData3::NormalType::INTERPOLATED)
        {
            const Color4& colorA = renderFog(calculateLighting(triangle.a, triangle.normalA), distance1);
            const Color4& colorB = renderFog(calculateLighting(triangle.b, triangle.normalB), distance2);
            const Color4& colorC = renderFog(calculateLighting(triangle.c, triangle.normalC), distance3);

            renderTriangle(renderer, totalColorAt(triangle, colorA, colorB, colorC, 0.0, 0.0), totalColorAt(triangle, colorA, colorB, colorC, 1.0, 0.0), totalColorAt(triangle, colorA, colorB, colorC, 0.0, 1.0), a, b, c);
        }
        else
        {
            const Vector3 normal = std::move(triangle.normal());
            const Color4& colorA = renderFog(calculateLighting(triangle.a, normal), distance1);
            const Color4& colorB = renderFog(calculateLighting(triangle.b, normal), distance2);
            const Color4& colorC = renderFog(calculateLighting(triangle.c, normal), distance3);

            renderTriangle(renderer, totalColorAt(triangle, colorA, colorB, colorC, 0.0, 0.0), totalColorAt(triangle, colorA, colorB, colorC, 1.0, 0.0), totalColorAt(triangle, colorA, colorB, colorC, 0.0, 1.0), a, b, c);
        }
    }
}
void Renderer3::renderBatchRaytraced(Image4& screen, const Rect2<double>& scope, double minDist, double maxDist) {
    depthBuffer = Grid2<uint32_t>((size_t)scope.width, (size_t)scope.height, (uint32_t)UINT32_MAX);
    normalBuffer = Grid2<Vector3>((size_t)scope.width, (size_t)scope.height, Vector3::zero);
    processFaces(scope);
    for (auto iterator = _processedFaces.begin(); iterator != _processedFaces.end(); ++iterator)
    {

    }
}
void Renderer3::renderBatchRaytraced(SDL_Renderer* renderer, const Rect2<double>& scope, double minDist, double maxDist) {
    processFaces(scope);
    for (auto iterator = _processedFaces.begin(); iterator != _processedFaces.end(); ++iterator)
    {

    }
}