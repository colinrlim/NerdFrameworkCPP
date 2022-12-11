#include <fstream>
#include <vector>
#include <string>
#include "MaterialManager.h"
#include "MeshParser.h"
#include "MeshQuad3.h"
#include "Format.h"
#include "Math.h"
#include "String.h"

Mesh* MeshParser::fromMesh(const Mesh& mesh) {
	std::vector<Vector3*> vertices;
	Collection3<MeshTriangle3> faces;
	for (size_t i = 0; i < mesh.vertices.size(); i++)
		vertices.push_back(new Vector3(*mesh.vertices[i]));
    for (auto iterator = mesh.faces.begin(); iterator != mesh.faces.end(); ++iterator) {
        const MeshTriangle3 triangle = **iterator;
		Vector3* a = nullptr;
		Vector3* b = nullptr;
		Vector3* c = nullptr;
		for (size_t i = 0; i < vertices.size() && (a == nullptr || b == nullptr || c == nullptr); i++) {
			if (*vertices[i] == triangle.a)
				a = vertices[i];
			else if (*vertices[i] == triangle.b)
				b = vertices[i];
			else if (*vertices[i] == triangle.c)
				c = vertices[i];
		}
		if (a != nullptr && b != nullptr && c != nullptr)
			faces.push_back(new MeshTriangle3(a, b, c));
	}
	return new Mesh(std::move(vertices), std::move(faces));
}
Mesh* MeshParser::fromFile(const char* filename, bool overrideNormalInterpolation, Material* material) {
	std::vector<Vector3*> vertices;
    std::vector<MeshTriangle3*> tris;

    std::vector<Vector2> textureCoords;
    std::vector<Vector3> normals;

    MaterialManager& materialManager = MaterialManager::getInstance();
    Material* currentMaterial = materialManager.getMaterial("None");
    if (material != nullptr)
        currentMaterial = material;

    String string(filename);

    /* Object (OBJ) Specifications
     * http://paulbourke.net/dataformats/obj/
     */

    if (string.endsWith(".obj")) {
        std::ifstream inStream(filename);
        for (std::string line; std::getline(inStream, line); )
        {
            std::vector<std::string> args = Format::split(line, ' ');
            if (line == "usemtl") {
                if (material == nullptr)
                    currentMaterial = materialManager.getMaterial(args[1]);
            } else if (line == "v") {
                vertices.push_back(new Vector3(std::stod(args[1]), std::stod(args[2]), std::stod(args[3])));
            } else if (line == "vt") {
                textureCoords.push_back(Vector2(std::stod(args[1]), std::stod(args[2])));
            } else if (line == "vn") {
                normals.push_back(Vector3(std::stod(args[1]), std::stod(args[2]), std::stod(args[3])));
            } else if (line == "f") {
                std::vector<Vector3*> faceVertices(3);
                std::vector<Vector2> faceTextures(3);
                std::vector<Vector3> faceNormals(3);
                for (int i = 1; i < args.size(); i++) {
                    std::vector<std::string> args1 = Format::split(args[i], '/');
                    faceVertices.push_back(vertices[(uint64_t)std::stoi(args1[0]) - 1]);
                    if (args1.size() >= 2 && args1[1] != "")
                        faceTextures.push_back(textureCoords[(uint64_t)std::stoi(args1[1]) - 1]);
                    if (args1.size() >= 3)
                        faceNormals.push_back(normals[(uint64_t)std::stoi(args1[2]) - 1]);
                }
                if (faceVertices.size() == 3) {
                    MeshTriangle3* triangle = new MeshTriangle3(faceVertices[0], faceVertices[1], faceVertices[2]);
                    if (faceTextures.size() == 3)
                    {
                        triangle->textureU = faceTextures[0];
                        triangle->textureV = faceTextures[1];
                        triangle->textureW = faceTextures[2];
                    }
                    if (faceNormals.size() == 3 && !overrideNormalInterpolation)
                    {
                        triangle->normalA = faceNormals[0];
                        triangle->normalB = faceNormals[1];
                        triangle->normalC = faceNormals[2];
                        triangle->normalType = RenderData3::NormalType::INTERPOLATED;
                    }
                    triangle->material = currentMaterial;
                    tris.push_back(triangle);
                } else if (faceVertices.size() == 4) {
                    MeshQuad3* quad = new MeshQuad3(faceVertices[0], faceVertices[1], faceVertices[2], faceVertices[3]);
                    if (faceTextures.size() == 4)
                    {
                        quad->textureU = faceTextures[0];
                        quad->textureV = faceTextures[1];
                        quad->textureW = faceTextures[2];
                        quad->textureX = faceTextures[3];
                    }
                    if (faceNormals.size() == 4 && !overrideNormalInterpolation)
                    {
                        quad->normalA = faceNormals[0];
                        quad->normalB = faceNormals[1];
                        quad->normalC = faceNormals[2];
                        quad->normalD = faceNormals[3];
                        quad->normalType = RenderData3::NormalType::INTERPOLATED;
                    }
                    quad->material = currentMaterial;
                    tris.push_back(quad->getMeshTriangle1());
                    tris.push_back(quad->getMeshTriangle2());
                }
            }
        }

        Collection3<MeshTriangle3> faces(tris);
        return new Mesh(std::move(vertices), std::move(faces));
    }
    return nullptr;
}

Mesh* MeshParser::fromCube(const Vector3& origin, double sideLength) {
	double v = sideLength / 2.0;
	Vector3* a = new Vector3(v, v, -v);
	Vector3* b = new Vector3(v, v, v);
	Vector3* c = new Vector3(-v, v, -v);
	Vector3* d = new Vector3(-v, v, v);
	Vector3* e = new Vector3(v, -v, -v);
	Vector3* f = new Vector3(v, -v, v);
	Vector3* g = new Vector3(-v, -v, -v);
	Vector3* h = new Vector3(-v, -v, v);

	std::vector<MeshTriangle3*> tris{
		new MeshTriangle3(b, d, f),
		new MeshTriangle3(h, f, d),
		new MeshTriangle3(b, a, d),
		new MeshTriangle3(c, d, a),
		new MeshTriangle3(d, c, h),
		new MeshTriangle3(g, h, c),
		new MeshTriangle3(h, g, f),
		new MeshTriangle3(e, f, g),
		new MeshTriangle3(f, e, b),
		new MeshTriangle3(a, b, e),
		new MeshTriangle3(a, e, c),
		new MeshTriangle3(g, c, e)
	};

	std::vector<Vector3*> vertices{ a, b, c, d, e, f, g, h };
	Collection3<MeshTriangle3> faces(tris);
	faces.setOrigin(origin);

    return new Mesh(std::move(vertices), std::move(faces));
}
Mesh* MeshParser::fromUVSphere(const Vector3& origin, double radius, int segments, int rings) {
	std::vector<Vector3*> vertices;
	Collection3<MeshTriangle3> faces;
    return new Mesh(std::move(vertices), std::move(faces));
}
Mesh* MeshParser::fromIcoSphere(const Vector3& origin, double radius, int iterations, RenderData3::NormalType normalType) {
    double goldenRatio = (1.0 + Math::sqrt(5)) / 2.0;
    Vector3* a = new Vector3(Vector3(goldenRatio, 1.0, 0.0).normalized());
    Vector3* b = new Vector3(Vector3(goldenRatio, -1.0, 0.0).normalized());
    Vector3* c = new Vector3(Vector3(-goldenRatio, -1.0, 0.0).normalized());
    Vector3* d = new Vector3(Vector3(-goldenRatio, 1.0, 0.0).normalized());
    Vector3* e = new Vector3(Vector3(1.0, 0.0, goldenRatio).normalized());
    Vector3* f = new Vector3(Vector3(-1.0, 0.0, goldenRatio).normalized());
    Vector3* g = new Vector3(Vector3(-1.0, 0.0, -goldenRatio).normalized());
    Vector3* h = new Vector3(Vector3(1.0, 0.0, -goldenRatio).normalized());
    Vector3* i = new Vector3(Vector3(0.0, goldenRatio, 1.0).normalized());
    Vector3* j = new Vector3(Vector3(0.0, goldenRatio, -1.0).normalized());
    Vector3* k = new Vector3(Vector3(0.0, -goldenRatio, -1.0).normalized());
    Vector3* l = new Vector3(Vector3(0.0, -goldenRatio, 1.0).normalized());

    std::vector<Vector3*> vertices{ a, b, c, d, e, f, g, h, i, j, k, l };
    std::vector<MeshTriangle3*> tris(20 * Math::ipow(4, iterations));

    // This was NOT poggers to make
    tris.push_back(new MeshTriangle3(e, l, b));
    tris.push_back(new MeshTriangle3(e, b, a));
    tris.push_back(new MeshTriangle3(e, a, i));
    tris.push_back(new MeshTriangle3(f, i, d));
    tris.push_back(new MeshTriangle3(f, d, c));
    tris.push_back(new MeshTriangle3(f, c, l));
    tris.push_back(new MeshTriangle3(e, i, f));
    tris.push_back(new MeshTriangle3(f, l, e));
    tris.push_back(new MeshTriangle3(b, k, h));
    tris.push_back(new MeshTriangle3(b, h, a));
    tris.push_back(new MeshTriangle3(h, j, a));
    tris.push_back(new MeshTriangle3(d, j, g));
    tris.push_back(new MeshTriangle3(d, g, c));
    tris.push_back(new MeshTriangle3(c, g, k));
    tris.push_back(new MeshTriangle3(g, j, h));
    tris.push_back(new MeshTriangle3(h, k, g));
    tris.push_back(new MeshTriangle3(i, a, j));
    tris.push_back(new MeshTriangle3(i, j, d));
    tris.push_back(new MeshTriangle3(l, c, k));
    tris.push_back(new MeshTriangle3(l, k, b));

    for (size_t i = 0; i < iterations; i++) {
        std::vector<MeshTriangle3*> newTris(tris);
        
        for (auto iterator = tris.begin(); iterator != tris.end(); ++iterator) {
            MeshTriangle3 triangle = *(*iterator);

            /*      A
             *    /   \
             *   /     \
             *  /       \
             * B ------- C
             */

             /*      A
              *    /   \
              *   D --- E
              *  / \   / \
              * B ---F--- C
              */

            Vector3* a = &triangle.a;
            Vector3* b = &triangle.b;
            Vector3* c = &triangle.c;
            Vector3* d = new Vector3(((*a + *b) / 2).normalized());
            Vector3* e = new Vector3(((*a + *c) / 2).normalized());
            Vector3* f = new Vector3(((*b + *c) / 2).normalized());

            newTris.push_back(new MeshTriangle3(a, d, e));
            newTris.push_back(new MeshTriangle3(d, b, f));
            newTris.push_back(new MeshTriangle3(e, f, c));
            newTris.push_back(new MeshTriangle3(d, f, e));

            vertices.push_back(d);
            vertices.push_back(e);
            vertices.push_back(f);
        }

        tris = newTris;
    }

    for (auto iterator = tris.begin(); iterator != tris.end(); ++iterator) {
        MeshTriangle3 triangle = *(*iterator);

        if (normalType == RenderData3::NormalType::INTERPOLATED)
        {
            triangle.normalType = normalType;
            triangle.normalA = triangle.a;
            triangle.normalB = triangle.b;
            triangle.normalC = triangle.c;
        }
        triangle.a *= radius;
        triangle.b *= radius;
        triangle.c *= radius;
    }

    Collection3<MeshTriangle3> faces(tris);
    faces.setOrigin(origin);

    return new Mesh(std::move(vertices), std::move(faces));
}
Mesh* MeshParser::fromQuadSphere(const Vector3& origin, double radius, int iterations, RenderData3::NormalType normalType) {
    Vector3* a = new Vector3(Vector3(1, 1, -1).normalized());
    Vector3* b = new Vector3(Vector3(1, 1, 1).normalized());
    Vector3* c = new Vector3(Vector3(-1, 1, -1).normalized());
    Vector3* d = new Vector3(Vector3(-1, 1, 1).normalized());
    Vector3* e = new Vector3(Vector3(1, -1, -1).normalized());
    Vector3* f = new Vector3(Vector3(1, -1, 1).normalized());
    Vector3* g = new Vector3(Vector3(-1, -1, -1).normalized());
    Vector3* h = new Vector3(Vector3(-1, -1, 1).normalized());

    std::vector<Vector3*> vertices{ a, b, c, d, e, f, g, h };
    std::vector<MeshQuad3*> quads;
    
    quads.push_back(new MeshQuad3(c, d, b, a));
    quads.push_back(new MeshQuad3(g, h, d, c));
    quads.push_back(new MeshQuad3(e, f, h, g));
    quads.push_back(new MeshQuad3(a, b, f, e));
    quads.push_back(new MeshQuad3(d, h, f, b));
    quads.push_back(new MeshQuad3(g, c, a, e));

    for (size_t i = 0; i < iterations; i++) {
        std::vector<MeshQuad3*> newQuads(quads);
        
        for (auto iterator = quads.begin(); iterator != quads.end(); ++iterator) {
            MeshQuad3 quad = *(*iterator);

            /* A ----- D
             * |       |
             * |       |
             * |       |
             * B ----- C
             */

             /* A - E - D
              * |   |   |
              * H - I - F
              * |   |   |
              * B - G - C
              */

            Vector3* a = &quad.a;
            Vector3* b = &quad.b;
            Vector3* c = &quad.c;
            Vector3* d = &quad.d;
            Vector3* e = new Vector3(((*a + *d) / 2.0).normalized());
            Vector3* f = new Vector3(((*d + *c) / 2.0).normalized());
            Vector3* g = new Vector3(((*c + *b) / 2.0).normalized());
            Vector3* h = new Vector3(((*b + *a) / 2.0).normalized());
            Vector3* i = new Vector3(((*a + *d + *c + *b) / 4.0).normalized());

            newQuads.push_back(new MeshQuad3(a, h, i, e));
            newQuads.push_back(new MeshQuad3(e, i, f, d));
            newQuads.push_back(new MeshQuad3(h, b, g, i));
            newQuads.push_back(new MeshQuad3(i, g, c, f));

            vertices.push_back(e);
            vertices.push_back(f);
            vertices.push_back(g);
            vertices.push_back(h);
            vertices.push_back(i);
        }

        quads = newQuads;
    }

    std::vector<MeshTriangle3*> tris;

    for (auto iterator = quads.begin(); iterator != quads.end(); ++iterator) {
        MeshQuad3 quad = *(*iterator);

        if (normalType == RenderData3::NormalType::INTERPOLATED)
        {
            quad.normalType = normalType;
            quad.normalA = quad.a;
            quad.normalB = quad.b;
            quad.normalC = quad.c;
            quad.normalD = quad.d;
        }

        quad.a *= radius;
        quad.b *= radius;
        quad.c *= radius;
        quad.d *= radius;
        tris.push_back(quad.getMeshTriangle1());
        tris.push_back(quad.getMeshTriangle2());
    }

	Collection3<MeshTriangle3> faces(tris);
    faces.setOrigin(origin);

    return new Mesh(std::move(vertices), std::move(faces));
}

void MeshParser::destroyMesh(Mesh* mesh) {
	delete mesh;
}