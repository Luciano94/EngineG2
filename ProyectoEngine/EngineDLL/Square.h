#pragma once
#include "Entity.h"
#include "Material.h"

class ENGINEDLL_API Square : public Entity
{
private:
	Material * material;
	bool shouldDispose;
	unsigned int bufferId;
	float * vertex;
	float * colorVertex;
	int vtxCount;

public:
	void Draw() override;
	Square(Renderer * render);
	~Square();
	void SetVertices(float * vertices, int count);
	void SetColorVertex(float * vertices, int count);
	void SetMaterial(Material* material);
	void Dispose();
};

