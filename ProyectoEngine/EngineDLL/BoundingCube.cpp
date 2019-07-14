#include "BoundingCube.h"



glm::vec3 BoundingCube::getVertex(int index)
{
	glm::vec4 globalRotatedPos(Cube[index].x, Cube[index].y, Cube[index].z, 1.0f);

	globalRotatedPos = renderPtr->getWMatrix() * globalRotatedPos;

	return (glm::vec3)globalRotatedPos;
}

void BoundingCube::setVertex(glm::vec3 _cube[8])
{
	for (int i = 0; i < 8; i++)
		Cube[i] = _cube[i];
}

BoundingCube::BoundingCube(Renderer * render)
{
	renderPtr = render;
}


BoundingCube::~BoundingCube()
{
}
