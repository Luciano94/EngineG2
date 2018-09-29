#include "Triangle.h"

Triangle::Triangle(Renderer *render) :Entity(render)
{
	shouldDispose = false;
	material = NULL;
	vertex = NULL;
	bufferId = -1;

	vertex = new float[9]
	{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	SetVertices(vertex, 3);
}

Triangle::~Triangle()
{
	Dispose();
}

void Triangle::SetVertices(float* vertices, int count)
{
	Dispose();
	vtxCount = count;
	shouldDispose = true;
	bufferId = render->GenBuffer(vertices, sizeof(float)* count * 3);

}

void Triangle::Draw()
{
	render->LoadIMatrix();
	render->SetWMatrix(WorldMatrix);

	if (material != NULL) {
		material->Bind("WVP");
		material->SetMatrixProperty(render->GetWVP());
	}

	render->BindDraw(0, bufferId);
	render->BeginDraw(0);
	render->DrawBuffer(bufferId, vtxCount);
	render->EndDraw(0);
}

void Triangle::SetMaterial(Material* material)
{
	this->material = material;
}

void Triangle::Dispose()
{
	if (shouldDispose)
	{
		render->DestroyBuffer(bufferId);
		delete[] vertex;
		shouldDispose = false;
	}
}
