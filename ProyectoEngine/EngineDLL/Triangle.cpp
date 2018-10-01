#include "Triangle.h"

Triangle::Triangle(Renderer *render) :Shape(render)
{

	vertex = new float[9]
	{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};
	colorVertex = new float[9]
	{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	SetVertices(vertex, 3);
	SetColorVertex(colorVertex, 3);
}

Triangle::~Triangle()
{
}

void Triangle::Draw()
{
	DrawMesh(GL_TRIANGLE_STRIP);
}
