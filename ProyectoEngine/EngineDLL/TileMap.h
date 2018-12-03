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
	int lastposXR;
	int lastposY;
	int lastposYR;

	vector<vector<Tile*>*> * viewSprite;
	vector<vector<int>*> * view;
	int viewW;
	int viewH;

	vector<vector<int>*> * level;
	int lvlW;
	int lvlH;
	int Xlvl;
	int Ylvl;
	
	void ChargeSprite();
	void LoadView();
	void LoadLevel(const char * filePath);
	void UpdateViewX();
	void UpdateViewXReverse();

	void UpdateViewY();
	void UpdateViewYReverse();


public:
	TileMap(const char * filePath, int winW, int winH, Renderer * render, Material * mat);
	~TileMap();

	void Draw();
	void Update();
};
