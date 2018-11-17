#include "BoundingBox.h"

BoundingBox::BoundingBox(glm::vec2 pos, unsigned int wigth, unsigned int heigth, bool setStatic):
pos(pos), wigth(wigth), heigth(heigth), staticBox(setStatic), isCollision(false){
}

float BoundingBox::GetX()
{
	return pos.x;
}

float BoundingBox::GetY()
{
	return pos.y;
}

glm::vec2 BoundingBox::GetPos()
{
	return pos;
}

void BoundingBox::SetPos(float x, float y){
	pos.x = x;
	pos.y = y;
}

float BoundingBox::GetWigth()
{
	return wigth;
}

float BoundingBox::GetHeigth()
{
	return heigth;
}

bool BoundingBox::GetCollision()
{
	return isCollision;
}

void BoundingBox::SetCollision(bool value)
{
	isCollision = value;
}

BoundingBox::~BoundingBox(){
}

bool BoundingBox::isStatic()
{
	return staticBox;
}
