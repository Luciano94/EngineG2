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
	render->setVMatrix(ViewMatrix);
	
	for (std::list<Component>::iterator it = components->begin(); it != components->end(); ++it)
	{
		it->update(deltaTime, render->getVMatrix());
	}

	for (std::list<Node>::iterator it = nodes->begin(); it != nodes->end(); ++it)
	{
		it->update(deltaTime, render->getVMatrix());
	}
}

void Node::draw()
{
}
