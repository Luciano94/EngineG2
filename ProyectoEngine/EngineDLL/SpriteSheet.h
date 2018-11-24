#pragma once
#include<list>
#include "Exports.h"

using namespace std;

class ENGINEDLL_API SpriteSheet
{
private: 
	float * uvArray;
	list<float *> * listOfUV;

	int spriteW, spriteH;
	int textureW, textureH;

public:
	SpriteSheet(int columns, int rows, int txW, int txH);

	float * GetSprite(int index);
	int GetSize();

	~SpriteSheet();
};

