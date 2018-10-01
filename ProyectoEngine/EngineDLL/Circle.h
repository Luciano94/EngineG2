#pragma once
#include "Shape.h"
#include "Material.h"

class ENGINEDLL_API Circle: public Shape
{
public:
	void Draw() override;
	Circle(Renderer * render);
	~Circle();
};

