#pragma once
#include "Exports.h"
class ENGINEDLL_API Material
{
	unsigned int ProgramID;
public:
	Material();
	~Material();
	unsigned int  LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	void Bind();
};

