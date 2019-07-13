#pragma once
#pragma warning(disable: 4251)
#include "Shape.h"
#include "GlobalDefinitions.h"
#include "Importer.h"

namespace physx
{
	class PxFoundation;
	class PxPhysics;
	class PxScene;
	class PxActor;
	class PxTransform;
	class PxRigidActor;
	class PxCapsuleGeometry;
	class PxMaterial;
}

struct meshes
{
	unsigned int bufferId;
	unsigned int uvBufferID;
	unsigned int indexBufferID;
	unsigned int texID;


	float * vertex;
	float * uvVertex;
	unsigned int * indices;

	Material * material;
	unsigned int programID;

	unsigned int vertexCount;
	unsigned int uvCount;
	unsigned int indexCount;

	bool shouldDispose;
	bool shouldDispouseIndices;
	bool shouldDispouseTexture;
};

class ENGINEDLL_API Mesh : public Shape
{
private:

	unsigned int texID;

	vector<meshes> * mesh;

	vector<MeshData> * meshInfo;
	Header texHed;

	void SetTextureVertex(int index);
	void SetIndexVertex(int index);
	void SetVertices(int index);
	void DisposeIndex();
	void DisposeTexture();
public:
	Mesh(Renderer * render, const char* fbxFile, const char * textureFile);
	void LoadMaterial(const char * bmpFile, unsigned int &texID, Material * material);
	~Mesh();

	void Draw();
};

