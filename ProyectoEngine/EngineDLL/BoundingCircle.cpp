#include "BoundingCircle.h"

BoundingCircle::BoundingCircle(glm::vec2 pos, unsigned int radius):
pos(pos), radius(radius){
}

glm::vec2 BoundingCircle::GetPos()
{
	return pos;
}

unsigned int BoundingCircle::GetRadius()
{
	return radius;
}

BoundingCircle::~BoundingCircle()
{
}
