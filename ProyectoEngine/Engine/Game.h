#pragma once
#include "GameBase.h"
#include "Triangle.h"
#include "Material.h"
#include <iostream>

using namespace std;
class Game : public GameBase {
private:
	int i;
	Triangle * tr1;
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


