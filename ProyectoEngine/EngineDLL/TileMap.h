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
	glm::vec3 LastCameraPos;
	glm::vec3 CurrentCameraPos;
	glm::vec3 DeltaCameraPos;

	float scrollX;
	float scrollY;
	int lastposX;
	int lastposY;

	vector<vector<Tile*>*> * viewSprite;

	vector<vector<int>*> * level;
	vector<vector<int>*> * view;
	int lvlW;
	int lvlH;
	int Xlvl;
	int Ylvl;
	void ChargeSprite();

	int * View;
	int viewW;
	int viewH;
	void LoadView();
	void UpdateView();


public:
	TileMap(const char * filePath, int winW, int winH, Renderer * render, Material * mat);
	~TileMap();

	void Draw();
	void Update();
	//void LoadLevel(const char* file);
};
