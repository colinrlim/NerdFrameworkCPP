#include "Mesh.h"

Mesh::Mesh(std::vector<Vector3*>&& vertices, Collection3<MeshTriangle3>&& faces) :
	vertices(std::move(vertices)),
	faces(std::move(faces))
{ }

Mesh::Mesh(const Mesh& rhs) : vertices(), faces() { }
Mesh::~Mesh() {
	for (auto iterator = vertices.begin(); iterator != vertices.end(); ++iterator)
		delete* iterator;
	for (auto iterator = faces.begin(); iterator != faces.end(); ++iterator)
		delete *iterator;
}
Mesh& Mesh::operator=(const Mesh& rhs) { return *this; }