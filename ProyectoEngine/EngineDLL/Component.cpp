#include "Component.h"



Component::Component(Renderer * render) :
Entity(render),
type(ComponentsType::nullComponent)
{
	cout << "Component" << endl;
}

void Component::Update()
{
}

void Component::Draw()
{
}


Component::~Component()
{
}
