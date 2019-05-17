#include "Mesh.h"



Mesh::Mesh(Renderer * render, const char* fbxFile) :Shape(render){
	shouldDispose = false;
	shouldDispouseTexture = false;
	shouldDispouseIndices = false;

	bufferId = -1;
	uvBufferID = -1;
	texID = -1;
	indexBufferID = -1;
	Importer::LoadMesh(fbxFile, mesh);

	vertexCount = mesh.vertexArray->size();
	indexCount = mesh.indexArray->size();
	uvCount = mesh.uvArray->size();

	vertex = new float[vertexCount];
	for (size_t i = 0; i < vertexCount; i++){
		vertex[i] = mesh.vertexArray->at(i);
	}
	SetVertices(vertex, vertexCount / 3);

	uvVertex = new float[uvCount];
	for (size_t i = 0; i < uvCount; i++) {
		uvVertex[i] = mesh.uvArray->at(i);
	}
	SetTextureVertex(uvVertex, uvCount /2);

	indices = new unsigned int[indexCount];
	for (size_t i = 0; i < indexCount; i++) {
		indices[i] = mesh.indexArray->at(i);
	}
	SetIndexVertex(indices, indexCount / 3);

}

void Mesh::LoadMaterial(const char * bmpFile) {
	Importer::LoadBMP(bmpFile, texHed);
	texID = render->ChargeTexture(texHed.width, texHed.height, texHed.data);
	material->BindTexture("myTextureSampler");
}

void Mesh::SetTextureVertex(float * vertices, int count) {
	DisposeTexture();

	uvCount = count;
	shouldDispouseTexture = true;
	uvBufferID = render->GenBuffer(vertices, sizeof(float)* count * 2);
}

void Mesh::DisposeIndex() {
	if (shouldDispouseIndices) {
		render->DestroyBuffer(indexBufferID);
		shouldDispouseIndices = false;
	}
}

void Mesh::DisposeTexture(){
	if (shouldDispouseIndices) {
		render->DestroyBuffer(uvBufferID);
		shouldDispouseIndices = false;
	}
}

void Mesh::SetIndexVertex(unsigned int * indices, int count){
	DisposeIndex();

	indexCount = count;
	shouldDispouseIndices = true;
	indexBufferID = render->GenMeshBuffer(indices, sizeof(int) * indexCount * 3);
}

void Mesh::Draw(){
	DrawIndexMesh(indices,indexCount * 3,indexBufferID, uvBufferID, texID);
}


Mesh::~Mesh(){
	DisposeIndex();
}
