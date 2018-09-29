#pragma once
#include "GameBase.h"
#include "Triangle.h"
#include "Material.h"
#include <iostream>

using namespace std;
class Game : public GameBase {
private:
	int i;
	float speed;
	float rotZ;
	float posX;
	Triangle * tr1;
	Triangle * tr2;
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


