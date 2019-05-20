#include "Importer.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include<glm/glm.hpp>
#include<glm\gtc\matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h> 
#include <assimp/postprocess.h>

void Importer::LoadBMP(const char * bmpFile, Header &hed){
	unsigned char header[54];

	FILE * file;
	fopen_s(&file, bmpFile, "rb");
	
	if (!bmpCorrectFormat(header, file)) {
		fopen_s(&file, "Default.bmp", "rb");
		if(bmpCorrectFormat(header, file))
			printf("Default image opened\n");
	}

	hed.dataPos = *(int*)&(header[0x0A]);
	hed.imageSize = *(int*)&(header[0x22]);
	hed.width = *(int*)&(header[0x12]);
	hed.height = *(int*)&(header[0x16]);

	if (hed.imageSize == 0)    
		hed.imageSize = hed.width * hed.height * 3;
	if (hed.dataPos == 0)      
		hed.dataPos = 54;

	hed.data = new unsigned char[hed.imageSize];
	fread(hed.data, 1, hed.imageSize, file);
	fclose(file);
}

bool Importer::bmpCorrectFormat(unsigned char header[], FILE *bmpFile)
{
	if (!bmpFile) {
		printf("Image could not be opened\n");
		return false;
	}

	if (fread(header, 1, 54, bmpFile) != 54) {
		printf("Not a correct BMP file\n");
		return false;
	}

	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		return false;
	}

	return true;
}

void Importer::LoadMesh(const char * fbxFile, std::vector<MeshData> * meshes){
	// Create an instance of the Importer class
	Assimp::Importer importer;
	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll 
	// propably to request more postprocessing than we do in this example.
	const aiScene* scene = importer.ReadFile(fbxFile,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	// If the import failed, report it
	if (!scene){
		return;
	}
	if (!scene->HasMeshes()) {
		return;
	}

	meshes->resize(scene->mNumMeshes);
	for (size_t i = 0; i < scene->mNumMeshes; i++){
		InitMesh(scene->mMeshes[i], meshes->at(i));
	}
}

void Importer::InitMesh(const aiMesh* paiMesh, MeshData & mesh)
{
	mesh.vertexArray = new std::vector<float>();
	mesh.uvArray = new std::vector<float>();
	mesh.indexArray = new std::vector<unsigned int>();

	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
		const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
		const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

		mesh.vertexArray->push_back(pPos->x);
		mesh.vertexArray->push_back(pPos->y);
		mesh.vertexArray->push_back(pPos->z);
		mesh.uvArray->push_back(pTexCoord->x);
		mesh.uvArray->push_back(pTexCoord->y);

	}
	for (unsigned int i = 0; i < paiMesh->mNumFaces; i++) {
		const aiFace& Face = paiMesh->mFaces[i];
		assert(Face.mNumIndices == 3);
		mesh.indexArray->push_back(Face.mIndices[0]);
		mesh.indexArray->push_back(Face.mIndices[1]);
		mesh.indexArray->push_back(Face.mIndices[2]);
	}
}

