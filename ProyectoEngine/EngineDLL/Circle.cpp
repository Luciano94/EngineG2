#include "Circle.h"


void Circle::Draw()
{
	DrawMesh(GL_TRIANGLE_FAN);
}

Circle::Circle(Renderer * render, float rdio, int trCant):Shape(render)
{
	cantOfTriangles = trCant;
	radius = rdio;
	vertexCount = cantOfTriangles * 3;
	angle = 0;
	degrees = 360.0f / cantOfTriangles;
	vertex = new float[vertexCount];
	glm::vec3 vec;

	for (int i = 0; i < vertexCount; i+=3)
	{
		vec = glm::vec3(cos(angle),sin(angle), 0) * radius;
		vertex[i] = vec.x;
		vertex[i + 1] = vec.y;
		vertex[i + 2] = vec.z;
		angle += degrees * PI / 180.0f;
	}

	SetVertices(vertex, cantOfTriangles);
	SetColorVertex(vertex, cantOfTriangles);

}

Circle::~Circle()
{
	delete[] vertex;
}
