#include "BoundingBox.h"

BoundingBox::BoundingBox(glm::vec2 pos, unsigned int wigth, unsigned int heigth, bool setStatic):
pos(pos), wigth(wigth), heigth(heigth), staticBox(setStatic){
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

void BoundingBox::SetPos(int x, int y){
	pos.x = x;
	pos.y = y;
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

bool BoundingBox::isStatic()
{
	return staticBox;
}
