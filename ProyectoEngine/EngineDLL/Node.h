#pragma once
#include "Exports.h"
#include "Component.h"
#include "Renderer.h"
#include "Entity.h"
#include "Mesh.h"
#include <vector>
#include<glm/glm.hpp>
#include<glm\gtc\matrix_transform.hpp>

using namespace std;

class ENGINEDLL_API Node: public Entity
{
private:
	Renderer * render;

	vector<Component *> * components;
	vector<Node *> * nodes;
public:
	string name = "";

	Node(Renderer * render);
	~Node();

	void addComponent(Component * comp);
	void removeComponent(int index);
	Component * getComponent(int index);
	Component * getComponent(ComponentsType type);
	void removeChild(int index);
	void addChild(Node * node);
	vector<Node*>* getChilds();
	vector<Component*>* getComponents();

	Node * getNode(int index);
	Node * getPlayer();
	void Update();
	void Draw();
};

