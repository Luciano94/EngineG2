#pragma once
#include "Exports.h"
#include "Component.h"
#include <list>

class ENGINEDLL_API Node
{
private:
	std::list<Component> * components;
	std::list<Node> * nodes;
public:
	Node();
	~Node();

	void addComponent(Component * comp);
	void removeComponent(int index);
	void removeChild(int index);
	void addChild(Node * node);
	void update(float deltaTime);
	void draw();
};

