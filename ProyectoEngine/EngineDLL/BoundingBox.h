#pragma once
#include "Exports.h"
#include "CollisionManager.h"
#include<glm/glm.hpp>
#include<glm\gtc\matrix_transform.hpp>

class ENGINEDLL_API BoundingBox{
private:
	glm::vec2 pos;
	unsigned int wigth;
	unsigned int heigth;
	Layers layer;
public:
	BoundingBox(glm::vec2 pos, unsigned int wigth, unsigned int heigth);
	unsigned int GetX();
	unsigned int GetY();
	glm::vec2 GetPos();
	unsigned int GetWigth();
	unsigned int GetHeigth();
	~BoundingBox();
};

