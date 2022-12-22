#pragma once

#include <SDL.h>
#include "QuickGrid2.h"
#include "Renderer2.h"
#include "RayCaster.h"
#include "Mesh.h"

class Renderer3 : public Renderer2
{
private:
	std::vector<MeshTriangle3*> _meshFaces;
	std::vector<MeshTriangle3*> _processedFaces;

	std::vector<Vector3*> _points;
	std::map<Vector3*, Vector2> _pointProjections;
	std::map<Vector3*, double> _pointDistances;

	Color4 totalatParameterization(const MeshTriangle3& triangle, const Color4& color1, const Color4& color2, const Color4& Color4, double t, double s) const;
	Color4 calculateLighting(const Vector3& point, const Vector3& normal) const;
	Color4 renderFog(const Color4& original, double distance) const;

	void processFaces(const Rect2<double>& scope);
public:
	RayCaster& camera;
	//Light3Caster cameraLight;

	Image4 cachedSkybox;
	QuickGrid2<uint32_t> depthBuffer;
	QuickGrid2<Vector3> normalBuffer;

	Color4 fog;

	Renderer3(RayCaster& camera);
	Renderer3(const UDim2& position, const UDim2& size, RayCaster& camera);

	void addMesh(Mesh* mesh);
	void removeMesh(const Mesh* mesh);
	
	void renderBatchRasterized(Image4& screen, const Rect2<double>& scope, double minDist = 0.0, double maxDist = std::numeric_limits<double>::max());
	void renderBatchRasterized(SDL_Renderer* renderer, const Rect2<double>& scope, double minDist = 0.0, double maxDist = std::numeric_limits<double>::max());
	void renderBatchRaytraced(Image4& screen, const Rect2<double>& scope, double minDist = 0.0, double maxDist = std::numeric_limits<double>::max());
	void renderBatchRaytraced(SDL_Renderer* renderer, const Rect2<double>& scope, double minDist = 0.0, double maxDist = std::numeric_limits<double>::max());
};

