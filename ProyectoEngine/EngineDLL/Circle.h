#pragma once
#include "Shape.h"
#include "Material.h"
#define PI 3.14159265359f

class ENGINEDLL_API Circle: public Shape
{
private:
	float radius;
	int cantOfTriangles;
	float angle;
	float degrees;
public:
	void Draw() override;
	Circle(Renderer * render, float rdio, int trCant);
	~Circle();
};