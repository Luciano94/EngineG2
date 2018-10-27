#pragma once
#include "Exports.h"
#include <fstream>

	struct Header
	{
		unsigned int dataPos;
		unsigned int width, height;
		unsigned int imageSize;
		unsigned char * data;
	};

class ENGINEDLL_API Importer
{
private:
	static bool bmpCorrectFormat(unsigned char header[], FILE *bmpFile);
public:
	static unsigned int LoadBMP(const char * bmpFile, Header &hed);
};

