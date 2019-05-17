#pragma once
#include "Shape.h"
#include "GlobalDefinitions.h"
#include "Importer.h"

struct meshes
{
	unsigned int bufferId;
	unsigned int uvBufferID;
	unsigned int indexBufferID;

	float * vertex;
	float * uvVertex;
	unsigned int * indices;

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
	Mesh(Renderer * render, const char * fbxFile);
	void LoadMaterial(const char * bmpFile);
	~Mesh();

	void Draw();
};

