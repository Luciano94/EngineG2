#pragma once
#include "Exports.h"
#include <fstream>

class ENGINEDLL_API Importer
{
private:
	struct Header
	{
		unsigned int dataPos;
		unsigned int width, height;
		unsigned int imageSize;
		unsigned char * data;
	};

	static bool bmpCorrectFormat(unsigned char header[], FILE *bmpFile);
public:
	static unsigned char LoadBMP(const char * bmpFile);
};

