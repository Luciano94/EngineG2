#include "SpriteSheet.h"



SpriteSheet::SpriteSheet(int columns, int rows, int txW, int txH):
textureW(txW), textureH(txH){
	vectorOfUV = new vector<float*>();
	
	float wf = 1.0f / columns;
	float hf = 1.0f / rows;
	int totSprites = columns * rows;

	for (int i = 0; i < totSprites; i++) {
		float x = (i % columns) * wf;
		float y = (i / columns) * hf;
		uvArray = new float[8]{
			x / textureW, 1 - ((y + hf) / textureH),
			x / textureW, 1 - y / textureH,
			(x + wf) / textureW , 1 - ((y + hf) / textureH),
			(x + wf) / textureW, 1 - (y / textureH)
		};
		vectorOfUV->push_back(uvArray);
	}
}

float * SpriteSheet::GetSprite(int index){
	return vectorOfUV->at(index);
}

int SpriteSheet::GetSize(){
	return vectorOfUV->size();
}

SpriteSheet::~SpriteSheet(){
	delete vectorOfUV;
}
