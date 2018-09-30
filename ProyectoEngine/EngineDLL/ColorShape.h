#pragma once
#include "Entity.h"
#include "Material.h"

class ENGINEDLL_API ColorShape: public Entity
{
private:
	Material * material;
	bool shouldDispose;
	int vertexCount;
	unsigned int bufferId;
public:
	ColorShape(Renderer * render);
	void Draw() override;
	void SetVertices(float * vertices, int count);
	void SetMaterial(Material* material);
	void Dispose();
	~ColorShape();
};

