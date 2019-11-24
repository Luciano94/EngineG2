#include "Mesh.h"

Mesh::Mesh(Renderer * render, const char * _textureFile, Camera * cam) :Component(render){
	type = ComponentsType::MeshRender;
	textureFile = _textureFile;
	meshStruct = new meshes;
	meshInfo = new MeshData();
	this->cam = cam;
	bCube = new BoundingCube(render);
	meshStruct->fbxFile = textureFile;
	meshStruct->shouldDispose = false;
	meshStruct->shouldDispouseIndices = false;
			
	meshStruct->bufferId = -1;
	meshStruct->uvBufferID = -1;
	meshStruct->indexBufferID = -1;

	drawerCube = new BoundingDrawer(render);
}

MeshData * Mesh::getMeshData()
{
	return meshInfo;
}

void Mesh::UpdateData(glm::vec3 min, glm::vec3 max)
{
	glm::vec3 auxVec;
	auxVec.x = max.x; 
	auxVec.y = max.y;
	auxVec.z = max.z;
	bCube->setVertex(0, auxVec);

	auxVec.x = max.x;
	auxVec.y = max.y;
	auxVec.z = min.z;
	bCube->setVertex(1, auxVec);

	auxVec.x = min.x;
	auxVec.y = max.y;
	auxVec.z = max.z;
	bCube->setVertex(2, auxVec);

	auxVec.x = min.x;
	auxVec.y = max.y;
	auxVec.z = min.z;
	bCube->setVertex(3, auxVec);

	auxVec.x = max.x;
	auxVec.y = min.y;
	auxVec.z = max.z;
	bCube->setVertex(4, auxVec);

	auxVec.x = max.x;
	auxVec.y = min.y;
	auxVec.z = min.z;
	bCube->setVertex(5, auxVec);

	auxVec.x = min.x;
	auxVec.y = min.y;
	auxVec.z = max.z;
	bCube->setVertex(6, auxVec);

	auxVec.x = min.x;
	auxVec.y = min.y;
	auxVec.z = min.z;
	bCube->setVertex(7, auxVec);
}

void Mesh::setBSP(bool _isBSP, Node * node)
{
	if (!_isBSP)
		return;

	isBsp = _isBSP;
	bspForward = glm::normalize((glm::vec3)(node->GetRotMatrix() * glm::vec4(0.0f,0.0f,1.0f,0.0f)));

	cam->addBSP(this, node->GetPos());
}

bool Mesh::getIsBsp()
{
	return isBsp;
}

glm::vec3 Mesh::getForwardBSP()
{
	return bspForward;
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

	drawerCube->SetVertices(bCube->getVertex(), CUBE_VERTEX);
	drawerCube->SetColorVertex(bCube->getVertex(), CUBE_VERTEX);
	drawerCube->SetMaterial(meshStruct->material);
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
	bool shouldDraw = true;
	if (!isBsp) {
		if (cam->boxInBSP(bCube) != States::INSIDE) {
			shouldDraw = false;
		}
		if (cam->boxInFrustum(bCube) != States::INSIDE) {
			shouldDraw = false;
		}
	}

	if (shouldDraw){
		if (!isBsp) {
			render->objectsDraws++;
		}
		//drawerCube->DrawMesh(GL_POINTS);
		//if(!isBsp) cout << "INSIDE" << endl;
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
		//if (!isBsp) cout << "OUTSIDE	>>" << meshStruct->fbxFile << endl;
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