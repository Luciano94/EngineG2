#pragma once
#include "Entity.h"
#include "Material.h"
#define GL_POINTS                         0x0000
#define GL_LINES                          0x0001
#define GL_LINE_LOOP                      0x0002
#define GL_LINE_STRIP                     0x0003
#define GL_TRIANGLES                      0x0004
#define GL_TRIANGLE_STRIP                 0x0005
#define GL_TRIANGLE_FAN                   0x0006

class ENGINEDLL_API Shape : public Entity
{
protected:
	Material * material;
	bool shouldDispose;
	bool shouldDisposeColor;
	int vertexCount;
	int colorVertexCount;
	unsigned int colorBufferId;
	unsigned int bufferId;
	float * vertex;
	float * colorVertex;
public:
	Shape(Renderer * render);
	virtual void Draw() = 0;
	void DrawMesh(int typeDraw);
	void SetVertices(float * vertices, int count);
	void SetColorVertex(float * vertices, int count);
	void SetMaterial(Material* material);
	void Dispose();
	void DisposeColor();
	~Shape();
};

