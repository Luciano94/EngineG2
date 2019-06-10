#pragma once
#include "Exports.h"
#include<glm/glm.hpp>
#include<glm\gtc\matrix_transform.hpp>

class ENGINEDLL_API Component
{
private:
	glm::mat4 ViewMatrix;
public:
	Component();
	void update(float deltaTime, glm::mat4 ViewMatrix);
	void draw();

	~Component();
};

