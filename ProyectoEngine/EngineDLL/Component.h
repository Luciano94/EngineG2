#pragma once
#include "Exports.h"
#include "GlobalDefinitions.h"
#include<glm/glm.hpp>
#include<glm\gtc\matrix_transform.hpp>

class ENGINEDLL_API Component
{
private:
	ComponentsType type;
public:
	void update(float deltaTime, glm::mat4 ViewMatrix);
	void draw();
	ComponentsType getComponentType() { return type; }

	Component(ComponentsType type);
	~Component();
};

