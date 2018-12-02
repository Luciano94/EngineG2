#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "CollisionManager.h" 
#include "Exports.h"
#include "Tile.h"


using namespace std;


class ENGINEDLL_API TileMap
{
private:

	Renderer * render;
	Material * material;
	CollisionManager * Instance;
	glm::vec3 CameraPos;
	float scrollX;

	vector<vector<Tile*>*> * viewSprite;

	vector<vector<int>*> * level;
	int lvlW;
	int lvlH;
	void ChargeSprite();

	int * View;
	int viewW;
	int viewH;
	void LoadView();


public:
	TileMap(const char * filePath, int winW, int winH, Renderer * render, Material * mat);
	~TileMap();

	void Draw();
	void Update();
	//void LoadLevel(const char* file);
};
