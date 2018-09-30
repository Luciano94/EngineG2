#include "Square.h"



Square::Square(Renderer *render) :Entity(render){
	shouldDispose = false;
	material = NULL;
	vertex = NULL;
	bufferId = -1;
	colorVertex = NULL;
	colorShape = new ColorShape(render);

	vertex = new float[12]
	{
		-1.0f, -1.0f, 0.f,
		-1.0f,  1.0f, 0.f,
		1.0f, -1.0f, 0.f,
		1.0f,  1.0f, 0.f
	};

	colorVertex = new float[12] 
	{
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
	};

	colorShape->SetVertices(colorVertex, 4);
	SetVertices(vertex, 4);
}

Square::~Square(){
	Dispose();
}

void Square::SetVertices(float* vertices, int count){
	Dispose();

	vtxCount = count;
	shouldDispose = true;
	bufferId = render->GenBuffer(vertices, sizeof(float)* count * 3);
}

void Square::Draw(){
	render->LoadIMatrix();
	render->SetWMatrix(WorldMatrix);

	if (material != NULL) {
		material->Bind("WVP");
		material->SetMatrixProperty(render->GetWVP());
	}

	/*dibujar cuadrado*/
	render->BeginDraw(0);
	render->BindDraw(0, bufferId);
	render->DrawBuffer(bufferId, vtxCount);
	colorShape->Draw();
	render->EndDraw(0);
}

void Square::SetMaterial(Material* material){
	this->material = material;
}

void Square::Dispose(){

	if (shouldDispose){
		render->DestroyBuffer(bufferId);
		delete[] vertex;
		delete[] colorVertex;
		shouldDispose = false;
	}
}
