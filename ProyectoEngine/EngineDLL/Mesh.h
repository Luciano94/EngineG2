#pragma once
#include "Shape.h"
#include <list>
#include "GlobalDefinitions.h"
#include "Importer.h"

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

