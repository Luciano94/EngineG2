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
	Input * input;
	void PlayerMovment();

	void CameraMovment(glm::vec3 playerPos);

	Tilemap * tilesito;

	int i;
	float speed;
	float rotZ;
	float posX;

	Sprite * player;
	
	Material * mat1;

protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	void OnDraw() override;
public:
	Game();
	~Game();
};


