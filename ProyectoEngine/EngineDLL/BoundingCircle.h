#pragma once
#include "Exports.h"
#include "GlobalDefinitions.h"
#include<glm/glm.hpp>
#include<glm\gtc\matrix_transform.hpp>

class ENGINEDLL_API BoundingCircle{
private:
	Layers layer;
	bool staticCircle;

	glm::vec2 pos;
	unsigned int radius;
public:
	bool isStatic();

	BoundingCircle(glm::vec2 pos, unsigned int radius, bool setStatic);
	glm::vec2 GetPos();
	unsigned int GetRadius();

	~BoundingCircle();
};

