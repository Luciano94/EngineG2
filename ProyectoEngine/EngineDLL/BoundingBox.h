#pragma once
#include "Exports.h"
#include "GlobalDefinitions.h"
#include<glm/glm.hpp>
#include<glm\gtc\matrix_transform.hpp>

class ENGINEDLL_API BoundingBox{
private:
	Layers layer;
	bool staticBox;

	bool isCollision;

	float wigth;
	float heigth;
	glm::vec2 pos;
public:
	BoundingBox(glm::vec2 pos, unsigned int wigth, unsigned int heigth, bool setStatic);
	~BoundingBox();

	bool isStatic();

	float GetX();
	float GetY();
	glm::vec2 GetPos();
	void SetPos(float x, float y);
	float GetWigth();
	float GetHeigth();
	bool GetCollision();
	void SetCollision(bool value);
};

