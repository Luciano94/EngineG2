#include "Circle.h"


void Circle::Draw()
{
	DrawMesh(GL_TRIANGLE_FAN);
}

Circle::Circle(Renderer * render):Shape(render)
{
	vertex = new float[12]
	{
		-0.2f, -0.2f,
		0.2f, -0.2f,
		0.2f, 0.2f,
		-0.2f, 0.2f
	};

	colorVertex = new float[12]
	{
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
	};

	SetColorVertex(colorVertex, 4);
	SetVertices(vertex, 4);
}

Circle::~Circle()
{
}
