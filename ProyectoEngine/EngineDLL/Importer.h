#pragma once
#include "Exports.h"
#include "GlobalDefinitions.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h> 
#include <assimp/postprocess.h>
#include <fstream>
#include <vector>

class Mesh;
class Node;
class Camera;
class Renderer;

class ENGINEDLL_API Importer
{
private:

	//BMP
	static bool bmpCorrectFormat(unsigned char header[], FILE *bmpFile);

	//Mesh
	static void InitMesh(const aiMesh* paiMesh, Mesh* meshComponent,Mesh * child, 
						glm::vec3 &mins, glm::vec3 &maxs, aiNode * node);

	static void ProcessNodes(const char * fbxFile, const char * textFile, Node * rootNode, 
							aiNode * node, const aiScene * scene, Renderer * render, 
							glm::vec3 &mins, glm::vec3 &maxs, Camera * cam);

	static void setNodeTransform(aiNode * aiNode, Node * node);

	static bool IsBspNode(const aiMesh * paiMesh,Node * node, Mesh * meshComponent);

public:
	static void LoadBMP(const char * bmpFile, Header &hed);
	
	static void LoadMesh(const char * fbxFile, const char * textFile,
						Node * rootNode, Renderer * render, Camera * cam);
};

