#include "Node.h"



Node::Node(Renderer * _render)
{
	render = _render;
}


Node::~Node()
{
}

void Node::addComponent(Component * comp)
{
}

Component Node::getComponent(ComponentsType type)
{
	for (std::list<Component>::iterator it = components->begin(); it != components->end(); ++it)
	{
		if (it->getComponentType == type)
			return *it;
	}
	return Component(ComponentsType::nullComponent);
}

void Node::removeComponent(int index)
{
}

void Node::removeChild(int index)
{
}

void Node::addChild(Node * node)
{
}

void Node::update(float deltaTime, glm::mat4 vMatrix)
{
	ViewMatrix *= render->getVMatrix();
	
	for (std::list<Node>::iterator it = nodes->begin(); it != nodes->end(); ++it)
	{
		it->update(deltaTime, render->getVMatrix());
	}

	for (std::list<Node>::iterator it = nodes->begin(); it != nodes->end(); ++it)
	{
		it->update(deltaTime, render->getVMatrix());
	}
	render->setVMatrix(ViewMatrix);
}

void Node::draw()
{
}
