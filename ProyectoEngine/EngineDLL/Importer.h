#pragma once
#include "Exports.h"
#include "GlobalDefinitions.h"
#include <fstream>


class ENGINEDLL_API Importer
{
private:
	static bool bmpCorrectFormat(unsigned char header[], FILE *bmpFile);
public:
	static void LoadBMP(const char * bmpFile, Header &hed);
	
	static void LoadMesh(const char * fbxFile, MeshData &mesh);
};

