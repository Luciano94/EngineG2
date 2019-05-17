#pragma once
#include "Shape.h"
#include "GlobalDefinitions.h"
#include "Importer.h"

class ENGINEDLL_API Mesh : public Shape
{
private:
	unsigned int bufferId;
	unsigned int uvBufferID;
	unsigned int texID;
	unsigned int indexBufferID;

	float * vertex;
	float * uvVertex;
	unsigned int * indices;

	unsigned int vertexCount;
	unsigned int uvCount;
	unsigned int indexCount;

	bool shouldDispose;
	bool shouldDispouseTexture;
	bool shouldDispouseIndices;

	MeshData mesh;
	Header texHed;

	void SetTextureVertex(float * vertices, int count);
	void SetIndexVertex(unsigned int * indices, int count);
	void DisposeIndex();
	void DisposeTexture();
public:
	Mesh(Renderer * render, const char * fbxFile);
	void LoadMaterial(const char * bmpFile);
	~Mesh();

	void Draw();
};

