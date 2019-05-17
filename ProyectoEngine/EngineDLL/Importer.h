#pragma once
#include "Exports.h"
#include "GlobalDefinitions.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h> 
#include <assimp/postprocess.h>
#include <fstream>
#include <vector>


class ENGINEDLL_API Importer
{
private:
	//BMP
	static bool bmpCorrectFormat(unsigned char header[], FILE *bmpFile);
	//Mesh
	static void InitMesh(const aiMesh* paiMesh, MeshData & mesh);

public:
	static void LoadBMP(const char * bmpFile, Header &hed);
	
	static void LoadMesh(const char * fbxFile, std::vector<MeshData> * meshes);
};

