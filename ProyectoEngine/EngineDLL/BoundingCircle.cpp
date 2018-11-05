#include "BoundingCircle.h"

bool BoundingCircle::isStatic()
{
	return staticCircle;
}

BoundingCircle::BoundingCircle(glm::vec2 pos, unsigned int radius, bool setStatic):
pos(pos), radius(radius), staticCircle(setStatic){
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
