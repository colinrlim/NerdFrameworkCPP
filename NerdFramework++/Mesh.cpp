#include "Mesh.h"

Mesh::Mesh(const std::vector<Vector3*>& vertices, const Collection3<MeshTriangle3>& faces) :
	vertices(vertices),
	faces(faces)
{ }

Mesh::Mesh(const Mesh& rhs) : vertices(), faces() { }
Mesh::~Mesh() {
	for (size_t i = 0; i < vertices.size(); i++)
		delete vertices[i];
	for (size_t i = 0; i < faces.objects.size(); i++)
		delete faces.objects[i];
}
Mesh& Mesh::operator=(const Mesh& rhs) { return *this; }