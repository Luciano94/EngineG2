#pragma once
#include "Renderer.h"
class ENGINEDLL_API Entity
{
protected:
	Renderer * render;
public:
	virtual void Draw() = 0;
	Entity(Renderer * renderPTR);
	~Entity();
};

