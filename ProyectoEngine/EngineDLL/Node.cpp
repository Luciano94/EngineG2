#include "Node.h"



Node::Node(Renderer * _render):
Entity(_render),
render(_render)
{
	cout << "Node" << endl;
	WorldMatrix = render->getVMatrix();
	nodes = new vector<Node *>();
	components = new vector<Component *>();
}


Node::~Node()
{
}

void Node::addComponent(Component * comp)
{
	components->push_back(comp);
}

Component * Node::getComponent(ComponentsType type)
{
	for (size_t i = 0; i < components->size(); i++)
	{
		if (components->at(i)->type == type)
			return components->at(i);
	}
	return nullptr;
}

void Node::removeComponent(int index)
{
	int i = 0;
	for (vector<Component*>::iterator it = components->begin(); it != components->end(); ++it)
	{
		if (i == index) 
		{
			components->erase(it);
			break;
		}
		i++;
	}
}

Component * Node::getComponent(int index) {
	if (index > components->size())
		return components->at(components->size()-1);
	return components->at(index);
}

void Node::removeChild(int index)
{
	int i = 0;
	for (vector<Node*>::iterator it = nodes->begin(); it != nodes->end(); ++it)
	{
		if (i == index) 
		{
			nodes->erase(it);
			break;
		}
		i++;
	}
}

void Node::addChild(Node * node)
{
	nodes->push_back(node);
}

vector<Node*>* Node::getChilds() {
	if (nodes == nullptr || nodes->size() == 0)
		return nullptr;
	return nodes;
}

vector<Component*>* Node::getComponents()
{
	return components;
}

Node * Node::getNode(int index)
{
	if (index >= nodes->size())
		return nodes->at(nodes->size() - 1);
	return nodes->at(index);
}

void Node::Update()
{	
	for (vector<Component*>::iterator it = components->begin(); it != components->end(); ++it)
	{
		(*it)->Update();
	}

	for (vector<Node*>::iterator it = nodes->begin(); it != nodes->end(); ++it)
	{
		(*it)->Update();
	}


}

void Node::Draw()
{
	//me guardo la MVP anterior
	glm::mat4 actualWorldMatrix = render->getWMatrix();
	glm::mat4 actualViewMatrix = render->getVMatrix();
	glm::mat4 actualProjectionMatrix = render->getPMatrix();

	//multiplico
	render->SetWMatrix(actualWorldMatrix * WorldMatrix);

	for (vector<Component*>::iterator it = components->begin(); it != components->end(); ++it)
	{
		(*it)->Draw();
	}
	for (vector<Node*>::iterator it = nodes->begin(); it != nodes->end(); ++it)
	{
		(*it)->Draw();
	}

	//las vuelvo a setear
	render->setVMatrix(actualViewMatrix);
	render->SetWMatrix(actualWorldMatrix);
	render->SetPMatrix(actualProjectionMatrix);
}
