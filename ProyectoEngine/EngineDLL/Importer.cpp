#include "Importer.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>

unsigned int Importer::LoadBMP(const char * bmpFile, Header &hed)
{
	unsigned char header[54];

	FILE * file;
	fopen_s(&file, bmpFile, "rb");
	
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

	hed.data = new unsigned char[hed.imageSize];
	fread(hed.data, 1, hed.imageSize, file);
	fclose(file);

	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, hed.width, hed.height, 0, GL_BGR, GL_UNSIGNED_BYTE, hed.data);

	// Poor filtering, or ...
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 

	// ... nice trilinear filtering ...
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// ... which requires mipmaps. Generate them automatically.
	glGenerateMipmap(GL_TEXTURE_2D);

	// Return the ID of the texture we just created
	return textureID;
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


