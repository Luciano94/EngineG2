#pragma once
#include<vector>
#include "Exports.h"

using namespace std;

class ENGINEDLL_API SpriteSheet
{
private: 
	float * uvArray;
	vector<float *> * vectorOfUV;

	int textureW, textureH;

public:
	SpriteSheet(int columns, int rows, int txW, int txH);

	float * GetSprite(int index);
	int GetSize();

	~SpriteSheet();
};

