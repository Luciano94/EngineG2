#include "Square.h"



Square::Square(Renderer *render) :Entity(render)
{
	shouldDispose = false;
	material = NULL;
	vertex = NULL;
	bufferId = -1;
	colorVertex = NULL;
	ColorBufferId = -1;

	vertex = new float[12]
	{
		-0.5f, -0.5f, 0.f,
		-0.5f,  0.5f, 0.f,
		0.5f, -0.5f, 0.f,
		0.5f,  0.5f, 0.f
	};

	colorVertex = new float[12] 
	{
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
	};

	SetVertices(vertex, 4);
	SetColorVertex(colorVertex, 4);
}

Square::~Square()
{
	Dispose(bufferId);
	Dispose(ColorBufferId);
}

void Square::SetVertices(float* vertices, int count)
{
	Dispose(bufferId);
	vtxCount = count;
	shouldDispose = true;
	bufferId = render->GenBuffer(vertices, sizeof(float)* count * 3);

}

void Square::SetColorVertex(float* vertices, int count) {
	Dispose(ColorBufferId);
	vtxColorCount = count;
	shouldDispose = true;
	ColorBufferId = render->GenColorBuffer(vertices, sizeof(float)* count * 3);
}

void Square::Draw()
{
	render->LoadIMatrix();
	render->SetWMatrix(WorldMatrix);

	if (material != NULL) {
		material->Bind("WVP");
		material->SetMatrixProperty(render->GetWVP());
	}

	/*dibujar cuadrado*/
	render->BindDraw(0, bufferId);
	render->BeginDraw(0);
	render->DrawBuffer(bufferId, vtxCount);
	render->EndDraw(0);
	/*pintar (? cuadrado*/
	render->BindDraw(1, ColorBufferId);
	render->BeginDraw(1);
	render->DrawBuffer(ColorBufferId, vtxColorCount);
	render->EndDraw(1);
}

void Square::SetMaterial(Material* material)
{
	this->material = material;
}

void Square::Dispose(unsigned int bufferId)
{
	if (shouldDispose)
	{
		render->DestroyBuffer(bufferId);
		delete[] vertex;
		shouldDispose = false;
	}
}
