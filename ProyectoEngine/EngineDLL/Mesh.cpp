#include "Mesh.h"



Mesh::Mesh(Renderer * render, const char* fbxFile, const char * textureFile) :Shape(render){
	mesh = new vector<meshes>();
	meshInfo = new vector<MeshData>();
	Importer::LoadMesh(fbxFile, meshInfo);
	mesh->resize(meshInfo->size());

	for (size_t i = 0; i < mesh->size(); i++) {
		mesh->at(i).shouldDispose = false;
		mesh->at(i).shouldDispouseIndices = false;

		mesh->at(i).bufferId = -1;
		mesh->at(i).uvBufferID = -1;
		mesh->at(i).indexBufferID = -1;
		mesh->at(i).vertexCount = meshInfo->at(i).vertexArray->size();
		mesh->at(i).indexCount = meshInfo->at(i).indexArray->size();
		mesh->at(i).uvCount = meshInfo->at(i).uvArray->size();

		mesh->at(i).vertex = new float[mesh->at(i).vertexCount];
		for (size_t j = 0; j < mesh->at(i).vertexCount; j++) {
			mesh->at(i).vertex[j] = meshInfo->at(i).vertexArray->at(j);
		}
		SetVertices(i);

		mesh->at(i).uvVertex = new float[mesh->at(i).uvCount];
		for (size_t j = 0; j < mesh->at(i).uvCount; j++) {
			mesh->at(i).uvVertex[j] = meshInfo->at(i).uvArray->at(j);
		}
		SetTextureVertex(i);

		mesh->at(i).indices = new unsigned int[mesh->at(i).indexCount];
		for (size_t j = 0; j < mesh->at(i).indexCount; j++) {
			mesh->at(i).indices[j] = meshInfo->at(i).indexArray->at(j);
		}
		SetIndexVertex(i);

		mesh->at(i).material = new Material();
		mesh->at(i).programID = mesh->at(i).material->LoadShaders("VertexTexture.glsl", "FragmentTexture.glsl");
		LoadMaterial(textureFile, mesh->at(i).texID, mesh->at(i).material);
	}
}

void Mesh::LoadMaterial(const char * bmpFile, unsigned int &texID, Material * material) {
	Importer::LoadBMP(bmpFile, texHed);
	texID = render->ChargeTexture(texHed.width, texHed.height, texHed.data);
	material->BindTexture("myTextureSampler");
}

void Mesh::SetVertices(int index) {
	Dispose();

	mesh->at(index).shouldDispose = true;
	mesh->at(index).bufferId = render->GenBuffer(mesh->at(index).vertex, 
								sizeof(float)* mesh->at(index).vertexCount);
}

void Mesh::SetTextureVertex(int index) {
	DisposeTexture();

	mesh->at(index).shouldDispouseTexture = true;
	mesh->at(index).uvBufferID = render->GenBuffer(mesh->at(index).uvVertex, 
								sizeof(float)* mesh->at(index).uvCount);
}

void Mesh::SetIndexVertex(int index){
	DisposeIndex();

	mesh->at(index).shouldDispouseIndices = true;
	mesh->at(index).indexBufferID = render->GenMeshBuffer(mesh->at(index).indices,
									sizeof(int) * mesh->at(index).indexCount);
}

void Mesh::DisposeIndex() {

}

void Mesh::DisposeTexture(){

}


void Mesh::Draw(){
	for (size_t i = 0; i < mesh->size(); i++){
		render->LoadIMatrix();
		render->SetWMatrix(WorldMatrix);

		if (mesh->at(i).material != NULL) {
			mesh->at(i).material->BindProgram();
			mesh->at(i).material->Bind("WVP");
			mesh->at(i).material->SetMatrixProperty(render->GetWVP());
		}

		render->BindTexture(mesh->at(i).texID, mesh->at(i).uvBufferID);
		render->BeginDraw(0);
		render->BindBuffer(0, mesh->at(i).bufferId, 3);
		render->BeginDraw(1);
		render->BindBuffer(1, mesh->at(i).uvBufferID, 2);
		render->DrawIndexMesh(mesh->at(i).indexCount, mesh->at(i).indexBufferID);
		render->EndDraw(0);
		render->EndDraw(1);
	}
}


Mesh::~Mesh(){
	for (size_t i = 0; i < mesh->size(); i++) {
		delete[] mesh->at(i).vertex;
		delete[] mesh->at(i).uvVertex;
		delete[] mesh->at(i).indices;
		delete mesh->at(i).material;
	}
	delete mesh;
	delete meshInfo;
}