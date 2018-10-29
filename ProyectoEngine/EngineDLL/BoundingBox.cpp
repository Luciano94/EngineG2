#include "BoundingBox.h"

BoundingBox::BoundingBox(glm::vec2 pos, unsigned int wigth, unsigned int heigth):
pos(pos), wigth(wigth), heigth(heigth){
}

unsigned int BoundingBox::GetX()
{
	return pos.x;
}

unsigned int BoundingBox::GetY()
{
	return pos.y;
}

glm::vec2 BoundingBox::GetPos()
{
	return pos;
}

unsigned int BoundingBox::GetWigth()
{
	return wigth;
}

unsigned int BoundingBox::GetHeigth()
{
	return heigth;
}

BoundingBox::~BoundingBox(){
}
