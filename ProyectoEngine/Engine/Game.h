#pragma once
#include "GameBase.h"
#include "CollisionManager.h"
#include "Triangle.h"
#include "Square.h"
#include "Circle.h"
#include "Sprite.h"
#include "Material.h"
#include "Importer.h"
#include <iostream>

using namespace std;
class Game : public GameBase {
private:
	int i;
	float speed;
	float rotZ;
	float posX;
	Square * sqr1;
	Triangle * tr1;
	Triangle * tr2;
	Circle * cir1;

	Sprite * spr1;
	Sprite * spr2;
	Sprite * spr3;
	Sprite * spr4;
	Sprite * spr5;
	
	Material * mat3;
	Material * mat2;
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


