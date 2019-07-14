#pragma once
#include "Exports.h"
#include "Renderer.h"
#include "GlobalDefinitions.h"
#include <iostream>
#include<glm/glm.hpp>
#include<glm\gtc\matrix_transform.hpp>

class ENGINEDLL_API BoundingCube
{
private:
	glm::vec3 Cube[8];
	Renderer * renderPtr;
public:
	glm::vec3 getVertex(int index);
	void setVertex(glm::vec3 _cube[8]);
	BoundingCube(Renderer * render);
	~BoundingCube();
};

