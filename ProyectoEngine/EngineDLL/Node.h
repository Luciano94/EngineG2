#pragma once
#include "Exports.h"
#include "Component.h"
#include "Renderer.h"
#include <list>
#include<glm/glm.hpp>
#include<glm\gtc\matrix_transform.hpp>

class ENGINEDLL_API Node
{
private:
	Renderer * render;

	std::list<Component *> * components;
	std::list<Node *> * nodes;

	glm::mat4 ViewMatrix;
public:
	Node(Renderer * render);
	~Node();

	void addComponent(Component * comp);
	void removeComponent(int index);
	Component * getComponent(ComponentsType type);
	void removeChild(int index);
	void addChild(Node * node);
	void update(float deltaTime, glm::mat4 ViewMatrix, int i);
	void draw();
};

