#pragma once
#include "Exports.h"
#include "Entity.h"
#include "Material.h"
#include "GlobalDefinitions.h"
#include<glm/glm.hpp>
#include<glm\gtc\matrix_transform.hpp>

class ENGINEDLL_API Component: public Entity
{
public:
	ComponentsType type;

	void Update(float deltaTime, glm::mat4 ViewMatrix);
	void Draw();
	Component(Renderer * render);
	~Component();
};

