#pragma once
#include "Shape.h"

class ENGINEDLL_API Mesh : public Shape
{
private:
	unsigned int bufferId;
	unsigned int colorBufferID;
	unsigned int indexBufferID;

	float * vertex;
	float * colorVertex;
	int * indices;

	int vertexCount;
	int colorCount;
	int indexCount;

	bool shouldDispose;
	bool shouldDispouseColor;
	bool shouldDispouseIndices;


public:
	Mesh(Renderer * render);
	~Mesh();

	void DisposeIndex();
	void SetIndexVertex(int * indices, int count);
	void Draw();
	//void DrawMesh(int typeDraw);
};

