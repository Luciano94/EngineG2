#pragma once
#include "Shape.h"
#include "Material.h"

class ENGINEDLL_API Square : public Shape
{
public:
	void Draw() override;
	Square(Renderer * render);
	~Square();
};

