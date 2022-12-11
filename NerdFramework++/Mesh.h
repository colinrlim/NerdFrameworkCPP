#pragma once

#include "Collection3.h"
#include "MeshTriangle3.h"

class Mesh
{
private:
	Mesh(std::vector<Vector3*>&& vertices, Collection3<MeshTriangle3>&& faces);

	Mesh(const Mesh& rhs);
	~Mesh();
	Mesh& operator=(const Mesh& rhs);

	friend class MeshParser;
public:
	const std::vector<Vector3*> vertices;
	Collection3<MeshTriangle3> faces;
};

