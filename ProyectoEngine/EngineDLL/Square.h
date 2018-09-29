#pragma once
#include "Entity.h"
#include "Material.h"

class ENGINEDLL_API Square : public Entity
{
private:
	Material * material;
	bool shouldDispose;
	float * vertex;
	int vtxCount;
	unsigned int bufferId;
	float * colorVertex;
	int vtxColorCount;
	unsigned int ColorBufferId;

public:
	void Draw() override;
	Square(Renderer * render);
	~Square();
	void SetVertices(float * vertices, int count);
	void SetColorVertex(float * vertices, int count);
	void SetMaterial(Material* material);
	void Dispose(unsigned int bufferId);
};

