#pragma once
#include "Exports.h"
#include "CollisionManager.h"
#include<glm/glm.hpp>
#include<glm\gtc\matrix_transform.hpp>

class BoundingCircle
{
private:
	glm::vec2 pos;
	unsigned int radius;
	Layers layer;
public:
	BoundingCircle(glm::vec2 pos, unsigned int radius);
	glm::vec2 GetPos();
	unsigned int GetRadius();

	~BoundingCircle();
};

