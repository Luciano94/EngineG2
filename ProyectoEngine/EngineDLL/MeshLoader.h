#pragma once
#include "Exports.h"
#include "GlobalDefinitions.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h> 
#include <assimp/postprocess.h>
#include <fstream>
#include <vector>
#include "Mesh.h"
#include "Node.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h> 
#include <assimp/postprocess.h>
#include "Camera.h"
using namespace std;
using namespace Assimp;

class Renderer;
class Mesh;
class Node;

class ENGINEDLL_API MeshLoader
{

private:
	MeshLoader();
	static MeshLoader *instance;
	const aiScene* scene = NULL;
	Assimp::Importer importer;
	void InitMesh(const aiMesh* _paiMesh, Mesh* _mesh);
    void ProcessNodes(const char * _texturePath, Node * _rootNode, aiNode * _node, const aiScene * _aiScene, Renderer * _renderer, Camera * _camera);
	void GenerateBoundingBox(Node * _rootNode);
	void IsBspNode(const aiMesh * paiMesh, Node * node, Mesh * meshComponent);
	void setNodeTransform(aiNode * aiNode, Node * node);
	glm::vec3 boundingBoxMin;
	glm::vec3 boundingBoxMax;
public:
	void LoadMesh(const char * _modelPath, const char * _texturePath, Node * _rootNode, Renderer* _renderer, Camera * _camera);
	static MeshLoader* GetInstance()
	{
		if (instance == NULL)
		{
			instance = new MeshLoader();
		}
		return instance;
	}
};

