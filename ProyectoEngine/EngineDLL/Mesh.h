#pragma once
#include "Component.h"
#include "BoundingCube.h"
#include "Node.h"
#include "Camera.h"
#include <list>
#include "GlobalDefinitions.h"
#include "Importer.h"

struct meshes
{
	const char * fbxFile;

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

class ENGINEDLL_API Mesh : public Component
{
private:

	unsigned int texID;

	meshes * meshStruct;
	const char * textureFile;
	MeshData * meshInfo;
	Header texHed;

	void SetTextureVertex();
	void SetIndexVertex();
	void SetVertices();
	void DisposeIndex();
	void DisposeTexture();
	Camera * cam;
public:

	BoundingCube * bCube;

	Mesh(Renderer * render, const char * _textureFile, Camera * cam);
	~Mesh();

	MeshData * getMeshData();
	void setMeshData(MeshData * m);
	void LoadMaterial(const char * bmpFile, unsigned int &texID, Material * material);
	void Draw() override;
};

