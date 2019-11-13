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
	glm::vec3 Cube[CUBE_VERTEX];
	Renderer * renderPtr;
public:
	glm::vec3 getVertex(int index);
	void setVertex(int index, glm::vec3 pos);
	void setVertex(glm::vec3 _cube[CUBE_VERTEX]);
	BoundingCube(Renderer * render);
	~BoundingCube();
};

