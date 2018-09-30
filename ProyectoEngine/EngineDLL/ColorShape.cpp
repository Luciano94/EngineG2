#include "ColorShape.h"



ColorShape::ColorShape(Renderer * render) :Entity(render){
	shouldDispose = false;
	material = NULL;
	bufferId = -1;
	vertexCount = -1;
}

void ColorShape::Draw(){
	render->LoadIMatrix();
	render->SetWMatrix(WorldMatrix);

	if (material != NULL) {
		material->Bind("WVP");
		material->SetMatrixProperty(render->GetWVP());
	}

	render->BeginDraw(1);
	render->BindDraw(1, bufferId);
	render->DrawBuffer(bufferId, vertexCount);
	render->EndDraw(1);
}

void ColorShape::SetVertices(float * vertices, int count){
	Dispose();

	vertexCount = count;
	shouldDispose = true;
	bufferId = render->GenBuffer(vertices, sizeof(float)* count * 3);
}

void ColorShape::SetMaterial(Material * material){
	this->material = material;
}

void ColorShape::Dispose(){
	if (shouldDispose){
		render->DestroyBuffer(bufferId);
		shouldDispose = false;
	}
}


ColorShape::~ColorShape(){
	Dispose();
}
