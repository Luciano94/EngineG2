#include "Mesh.h"

Mesh::Mesh(Renderer * render, const char * _textureFile, Camera * cam) :Component(render){
	type = ComponentsType::MeshRender;
	textureFile = _textureFile;
	meshStruct = new meshes;
	meshInfo = new MeshData();
	this->cam = cam;
	bCube = new BoundingCube(render);

	meshStruct->shouldDispose = false;
	meshStruct->shouldDispouseIndices = false;
			
	meshStruct->bufferId = -1;
	meshStruct->uvBufferID = -1;
	meshStruct->indexBufferID = -1;
}

MeshData * Mesh::getMeshData()
{
	return meshInfo;
}

void Mesh::setMeshData(MeshData * m) 
{
	meshInfo = m;
	meshStruct->vertexCount = meshInfo->vertexArray->size();
	meshStruct->indexCount = meshInfo->indexArray->size();
	meshStruct->uvCount = meshInfo->uvArray->size();

	meshStruct->vertex = new float[meshStruct->vertexCount];
	for (size_t j = 0; j < meshStruct->vertexCount; j++) {
		meshStruct->vertex[j] = meshInfo->vertexArray->at(j);
	}
	SetVertices();

	meshStruct->uvVertex = new float[meshStruct->uvCount];
	for (size_t j = 0; j < meshStruct->uvCount; j++) {
		meshStruct->uvVertex[j] = meshInfo->uvArray->at(j);
	}
	SetTextureVertex();

	meshStruct->indices = new unsigned int[meshStruct->indexCount];
	for (size_t j = 0; j < meshStruct->indexCount; j++) {
		meshStruct->indices[j] = meshInfo->indexArray->at(j);
	}
	SetIndexVertex();

	meshStruct->material = new Material();
	meshStruct->programID = meshStruct->material->LoadShaders("VertexTexture.glsl", "FragmentTexture.glsl");
	LoadMaterial(textureFile, meshStruct->texID, meshStruct->material);

}

void Mesh::LoadMaterial(const char * bmpFile, unsigned int &texID, Material * material) {
	Importer::LoadBMP(bmpFile, texHed);
	texID = render->ChargeTexture(texHed.width, texHed.height, texHed.data);
	material->BindTexture("myTextureSampler");
}

void Mesh::SetVertices() {

	meshStruct->shouldDispose = true;
	meshStruct->bufferId = render->GenBuffer(meshStruct->vertex,
								sizeof(float)* meshStruct->vertexCount);
}

void Mesh::SetTextureVertex() {
	DisposeTexture();

	meshStruct->shouldDispouseTexture = true;
	meshStruct->uvBufferID = render->GenBuffer(meshStruct->uvVertex,
								sizeof(float)* meshStruct->uvCount);
}

void Mesh::SetIndexVertex(){
	DisposeIndex();

	meshStruct->shouldDispouseIndices = true;
	meshStruct->indexBufferID = render->GenMeshBuffer(meshStruct->indices,
									sizeof(int) * meshStruct->indexCount);
}

void Mesh::DisposeIndex() {

}

void Mesh::DisposeTexture(){

}


void Mesh::Draw() {
	if (cam->boxInFrustum(bCube) == States::INSIDE ||
		cam->boxInFrustum(bCube) == States::INTERSECT) {
		
		cout <<"INSIDE"<< endl;
		if (meshStruct->material != NULL) {
			meshStruct->material->BindProgram();
			meshStruct->material->Bind("WVP");
			meshStruct->material->SetMatrixProperty(render->GetWVP());
		}

		render->BindTexture(meshStruct->texID, meshStruct->uvBufferID);
		render->BeginDraw(0);
		render->BindBuffer(0, meshStruct->bufferId, 3);
		render->BeginDraw(1);
		render->BindBuffer(1, meshStruct->uvBufferID, 2);
		render->DrawIndexMesh(meshStruct->indexCount, meshStruct->indexBufferID);
		render->EndDraw(0);
		render->EndDraw(1);
	}
	else {
		cout << "OUTSIDE" << endl;
	}
}



Mesh::~Mesh(){
	delete[] meshStruct->vertex;
	delete[] meshStruct->uvVertex;
	delete[] meshStruct->indices;
	delete meshStruct->material;
	delete meshStruct;
	delete meshInfo;
	delete bCube;
}