#pragma once
#include "Exports.h"
#include "GlobalDefinitions.h"
#include<glm/glm.hpp>
#include<glm\gtc\matrix_transform.hpp>

class ENGINEDLL_API BoundingBox{
private:
	Layers layer;
	bool staticBox;

	unsigned int wigth;
	unsigned int heigth;
	glm::vec2 pos;
public:
	BoundingBox(glm::vec2 pos, unsigned int wigth, unsigned int heigth, bool setStatic);
	~BoundingBox();

	bool isStatic();

	unsigned int GetX();
	unsigned int GetY();
	glm::vec2 GetPos();
	void SetPos(int x, int y);
	unsigned int GetWigth();
	unsigned int GetHeigth();
};

