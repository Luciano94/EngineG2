#include "BoundingCube.h"



glm::vec3 BoundingCube::getVertex(int index)
{
	glm::vec4 globalRotatedPos(Cube[index].x, Cube[index].y, Cube[index].z, 1.0f);

	globalRotatedPos = renderPtr->getWMatrix() * globalRotatedPos;

	return (glm::vec3)globalRotatedPos;
}

float * BoundingCube::getVertex()
{
	float * result = new float[CUBE_VERTEX * 3];
	int cantVetex = 0;
	for (size_t i = 0; i < CUBE_VERTEX; i++)
	{
		glm::vec3 cube = getVertex(i);
		result[i] = cube.x;
		result[i + 1] = cube.y;
		result[i + 2] = cube.z;
		cantVetex += 3;
	}
	return result;
}

void BoundingCube::setVertex(int index, glm::vec3 pos) {
	Cube[index].x = pos.x; Cube[index].y = pos.y; Cube[index].z, pos.z;
}

void BoundingCube::setVertex(glm::vec3 _cube[CUBE_VERTEX])
{
	for (int i = 0; i < CUBE_VERTEX; i++)
		Cube[i] = _cube[i];
}

BoundingCube::BoundingCube(Renderer * render)
{
	renderPtr = render;
}


BoundingCube::~BoundingCube()
{
}
