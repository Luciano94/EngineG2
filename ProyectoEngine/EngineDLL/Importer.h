#pragma once
#include "Exports.h"
#include "Node.h"
#include "GlobalDefinitions.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h> 
#include <assimp/postprocess.h>
#include <fstream>
#include <vector>
//#include "Mesh.h"

class Mesh;

class ENGINEDLL_API Importer
{
private:
	//BMP
	static bool bmpCorrectFormat(unsigned char header[], FILE *bmpFile);
	//Mesh
	static void InitMesh(const aiMesh* paiMesh, Mesh* mesh);
	static void ProcessNodes(const char * fbxFile, const char * textFile, Node * rootNode, 
							aiNode * node, const aiScene * scene, Renderer * render);

public:
	static void LoadBMP(const char * bmpFile, Header &hed);
	
	static void LoadMesh(const char * fbxFile, const char * textFile, Node * rootNode, Renderer * render);
};

