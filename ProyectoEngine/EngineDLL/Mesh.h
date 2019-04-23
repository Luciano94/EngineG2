#pragma once
#include "Entity.h"
#include <vector>
class ENGINEDLL_API Mesh: public Entity
{
private:
	unsigned int bufferId;
	float * vertex;
	int vertexCount;
	bool shouldDispose;

	std::vector<unsigned int> indices;

public:
	Mesh(Renderer * render);
	~Mesh();
};

