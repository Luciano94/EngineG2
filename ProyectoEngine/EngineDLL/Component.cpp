#include "Component.h"



Component::Component(ComponentsType _type):
type(_type)
{
}

void Component::update(float deltaTime, glm::mat4 ViewMatrix)
{
}

void Component::draw()
{
}


Component::~Component()
{
}
