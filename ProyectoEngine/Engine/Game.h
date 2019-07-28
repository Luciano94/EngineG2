#pragma once
#include "GameBase.h"
#include "CollisionManager.h"
#include "Triangle.h"
#include "Square.h"
#include "Circle.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Material.h"
#include "Importer.h"
#include <iostream>

using namespace std;
class Game : public GameBase {
private:

	Tilemap * tilesito;

	int i;
	float speed;
	float rotZ;
	float posX;

	Sprite * spr1;
	Sprite * spr2;
	Sprite * spr3;
	
	Material * mat1;
	Material * mat2;

protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	void OnDraw() override;
public:
	Game();
	~Game();
};


