#include "Importer.h"


unsigned char Importer::LoadBMP(const char * bmpFile)
{
	unsigned char header[54];

	FILE * file;
	fopen_s(&file, bmpFile, "rb");
	
	Header hed;
	
	if (!bmpCorrectFormat(header, file)) 
		return NULL;

	hed.dataPos = *(int*)&(header[0x0A]);
	hed.imageSize = *(int*)&(header[0x22]);
	hed.width = *(int*)&(header[0x12]);
	hed.height = *(int*)&(header[0x16]);

	if (hed.imageSize == 0)    
		hed.imageSize = hed.width * hed.height * 3;
	if (hed.dataPos == 0)      
		hed.dataPos = 54;

	unsigned char *data = new unsigned char[hed.imageSize];
	fread(data, 1, hed.imageSize, file);
	fclose(file);
	return *data;
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


