#pragma once
#include "Exports.h"
#include<glm/glm.hpp>
#include<glm\gtc\matrix_transform.hpp>

class ENGINEDLL_API Material
{
	unsigned int ProgramID;
	unsigned int matrixID;
	unsigned int textureID;
public:
	Material();
	~Material();
	unsigned int  LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	void SetMatrixProperty(glm::mat4 &mat);
	
	void Bind(const char* name);
	void BindTexture(const char* name);
	void BindProgram();
};

