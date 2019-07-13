#include "Node.h"



Node::Node(Renderer * _render):
render(_render)
{
	nodes = new std::list<Node *>();
	components = new std::list<Component>();
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
		if (it->type == type)
			return *it;
	}
	return Component(render);
}

void Node::removeComponent(int index)
{
	int i = 0;
	for (std::list<Component>::iterator it = components->begin(); it != components->end(); ++it)
	{
		i++;
		if (i == index) 
		{
			components->erase(it);
			break;
		}
	}
}

void Node::removeChild(int index)
{
	int i = 0;
	for (std::list<Node*>::iterator it = nodes->begin(); it != nodes->end(); ++it)
	{
		i++;
		if (i == index) 
		{
			nodes->erase(it);
			break;
		}
	}
}

void Node::addChild(Node * node)
{
	nodes->push_back(node);
}

void Node::update(float deltaTime, glm::mat4 vMatrix, int i)
{
	ViewMatrix *= render->getVMatrix();
	for (std::list<Component>::iterator it = components->begin(); it != components->end(); ++it)
	{
		it->Update(deltaTime, ViewMatrix);
	}
	for (std::list<Node*>::iterator it = nodes->begin(); it != nodes->end(); ++it)
	{
		(*it)->update(deltaTime, render->getVMatrix(), i+1);
	}
	render->setVMatrix(ViewMatrix);
}

void Node::draw()
{
	for (std::list<Component>::iterator it = components->begin(); it != components->end(); ++it)
	{
		it->Draw();
	}
	for (std::list<Node*>::iterator it = nodes->begin(); it != nodes->end(); ++it)
	{
		(*it)->draw();
	}
}
