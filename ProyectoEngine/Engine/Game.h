#pragma once
#include "GameBase.h"
#include "CollisionManager.h"
#include "Triangle.h"
#include "Square.h"
#include "Circle.h"
#include "Input.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Material.h"
#include "Importer.h"
#include <iostream>

using namespace std;
class Game : public GameBase {
private:
	/*Input Manager*/
	Input * input;
	
	/*Game Logic*/
	void PlayerMovment();
	void CameraMovment(glm::vec3 playerPos);
	bool gameStart = false;
	bool gameFinish = false;
	bool resolveTileCollision();

	/*Game elements*/
	Sprite * player;

	/*Text*/
	Sprite * startCount;
	Sprite * winText;
	Sprite * loseText;
	float textTime;
	void showWin();
	void showLose();


	Sprite * obstacle;
	Sprite * obstacle1;
	Sprite * obstacle2;

	Tilemap * tilesito;
	Material * mat1;

	/*Global Speed*/
	float speed;

	

protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	void OnDraw() override;
public:
	Game();
	~Game();
};


