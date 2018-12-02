#pragma once
#include "Sprite.h"
#include <vector>
#include "Exports.h"
class ENGINEDLL_API Tile: public Sprite
{
private:
	vector<int> * textures;
public:
	Tile(Renderer * render, int columns, int rows);
	void AddTexture(const char * bmpFile);
	void ChangeTexture(int i);
	~Tile();
};

