#include "Importer.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h> 
#include <assimp/postprocess.h>

void Importer::LoadBMP(const char * bmpFile, Header &hed){
	unsigned char header[54];

	FILE * file;
	fopen_s(&file, bmpFile, "rb");
	
	if (!bmpCorrectFormat(header, file))
		hed.data = NULL;

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

void Importer::LoadMesh(const char * fbxFile, MeshData & mesh){
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
	if (scene->HasMeshes()) {
		scene->mMeshes;
	}
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


