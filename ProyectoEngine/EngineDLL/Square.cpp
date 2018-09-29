#include "Square.h"



Square::Square(Renderer *render) :Entity(render)
{
	shouldDispose = false;
	material = NULL;
	vertex = NULL;
	bufferId = -1;

	vertex = new float[12]
	{
		-0.5f, -0.5f, 0.f,
		-0.5f,  0.5f, 0.f,
		0.5f, -0.5f, 0.f,
		0.5f,  0.5f, 0.f
	};

	colorVertex = new float[12] 
	{
		1.f, 0.f, 0.f,
		0.f, 1.f, 0.f,
		0.f, 0.f, 1.f,
		1.f, 1.f, 0.f
	};

	SetVertices(vertex, 4);
}

Square::~Square()
{
	Dispose();
}

void Square::SetVertices(float* vertices, int count)
{
	Dispose();
	vtxCount = count;
	shouldDispose = true;
	bufferId = render->GenBuffer(vertices, sizeof(float)* count * 3);

}

void Square::SetColorVertex(float* vertices, int count) {
	
}

void Square::Draw()
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

void Square::SetMaterial(Material* material)
{
	this->material = material;
}

void Square::Dispose()
{
	if (shouldDispose)
	{
		render->DestroyBuffer(bufferId);
		delete[] vertex;
		shouldDispose = false;
	}
}
