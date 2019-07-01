#include "Node.h"



Node::Node(Renderer * _render)
{
	render = _render;
}


Node::~Node()
{
}

void Node::addComponent(Component comp)
{
	components->push_back(comp);
}

Component Node::getComponent(ComponentsType type)
{
	for (std::list<Component>::iterator it = components->begin(); it != components->end(); ++it)
	{
		if (it->getComponentType() == type)
			return *it;
	}
	return Component(ComponentsType::nullComponent);
}

void Node::removeComponent(int index)
{
	int i = 0;
	for (std::list<Component>::iterator it = components->begin(); it != components->end(); ++it)
	{
		i++;
		if (i == index) {
			components->erase(it);
			break;
		}
	}
}

void Node::removeChild(int index)
{
	int i = 0;
	for (std::list<Node>::iterator it = nodes->begin(); it != nodes->end(); ++it)
	{
		i++;
		if (i == index) {
			nodes->erase(it);
			break;
		}
	}
}

void Node::addChild(Node node)
{
	nodes->push_back(node);
}

void Node::update(float deltaTime, glm::mat4 vMatrix)
{
	ViewMatrix *= render->getVMatrix();
	
	for (std::list<Node>::iterator it = nodes->begin(); it != nodes->end(); ++it)
	{
		it->update(deltaTime, render->getVMatrix());
	}
	render->setVMatrix(ViewMatrix);
}

void Node::draw()
{
	for (std::list<Node>::iterator it = nodes->begin(); it != nodes->end(); ++it)
	{
		it->draw();
	}

	Component comp = getComponent(ComponentsType::MeshRender);
	if (comp.getComponentType() != ComponentsType::nullComponent)
		comp.draw();
}
