#include "Sprite.h"


Sprite::Sprite(Renderer * render): Shape(render){
	vertex = new float[12]
	{
		-1.0f, -1.0f, 0.f,
		-1.0f,  1.0f, 0.f,
		1.0f, -1.0f, 0.f,
		1.0f,  1.0f, 0.f
	};
	SetVertices(vertex, 4);

	uvArray = new float[8]
	{
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
	};
	SetTextureVertex(uvArray, 4);
}

void Sprite::SetTextureVertex(float * vertices, int count){
	DispouseTexture();
	
	uvVtxCount = count;
	shouldDispouseTexture = true;
	uvBufferID = render->GenBuffer(vertices, sizeof(float)* count * 2);
}


void Sprite::LoadMaterial(const char * bmpFile) {
	Importer::LoadBMP(bmpFile, texture);
	textureID = render->ChargeTexture(texture.width, texture.height, texture.data);
	material->BindTexture("myTextureSampler");
}

void Sprite::DispouseTexture(){
	if (shouldDispouseTexture) {
		render->DestroyBuffer(uvBufferID);
		shouldDispouseTexture = false;
	}
}



void Sprite::DrawMeshWhitTexture(int typeDraw){
	render->LoadIMatrix();
	render->SetWMatrix(WorldMatrix);

	if (material != NULL) {
		material->BindProgram();
		material->Bind("WVP");
		material->SetMatrixProperty(render->GetWVP());
	}

	render->BindTexture(textureID, uvBufferID);
	render->BeginDraw(0);
	render->BindBuffer(0, bufferId, 3);
	render->BeginDraw(1);
	render->BindBuffer(1, uvBufferID, 2);
	render->DrawBuffer(vertexCount, typeDraw);
	render->EndDraw(0);
	render->EndDraw(1);
}

void Sprite::Draw(){
	DrawMeshWhitTexture(GL_TRIANGLE_STRIP);
}

Sprite::~Sprite(){
	delete[] vertex;
	delete[] uvArray;
}
