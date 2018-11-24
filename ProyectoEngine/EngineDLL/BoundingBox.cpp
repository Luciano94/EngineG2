#include "BoundingBox.h"

BoundingBox::BoundingBox(glm::vec2 pos, unsigned int width, unsigned int heigth, bool setStatic, float mass):
pos(pos), width(width), heigth(heigth), staticBox(setStatic), isCollision(false), mass(mass){
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

float BoundingBox::GetWidth()
{
	return width;
}

float BoundingBox::GetHeigth()
{
	return heigth;
}

bool BoundingBox::GetCollision()
{
	return isCollision;
}

float BoundingBox::GetMass()
{
	return mass;
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
