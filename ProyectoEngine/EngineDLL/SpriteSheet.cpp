#include "SpriteSheet.h"



SpriteSheet::SpriteSheet(int columns, int rows, int txW, int txH):
textureW(txW), textureH(txH){
	
	listOfUV = new list<float *>();
	
	float wf = 1.0f / columns;
	float hf = 1.0f / rows;
	int totSprites = columns * rows;

	for (int i = 0; i < totSprites; i++) {
		float x = (i % totSprites) * wf;
		float y = (i / totSprites) * hf;
		uvArray = new float[8]{
			x / textureW, 1 - ((y + hf) / textureH),
			x / textureW, 1 -  y / textureH,
			(x + wf) / textureW , 1 - ((y + hf) / textureH),
			(x + wf) / textureW, 1 - y/ textureH
		};
		listOfUV->push_back(uvArray);
	}
}

float * SpriteSheet::GetSprite(int index)
{
	int inx = 0;
	for (list<float *>::iterator i = listOfUV->begin(); i != listOfUV->end() ; i++){
		if (inx == index)
			return *i;
		else inx++;
	}
}

int SpriteSheet::GetSize()
{
	return listOfUV->size();
}




SpriteSheet::~SpriteSheet()
{
}
