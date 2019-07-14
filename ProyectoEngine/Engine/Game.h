#pragma once
#include "GameBase.h"
#include "CollisionManager.h"
#include "Triangle.h"
#include "Square.h"
#include "Circle.h"
#include "Mesh.h"
#include "TileMap.h"
#include "Material.h"
#include "Importer.h"
#include "Input.h"
#include "Camera.h"
#include "Shape.h"
#include "Node.h"
#include <iostream>

using namespace std;
class Game : public GameBase {
private:

	//TileMap * tilesito;

	int i;
	float speed;
	float rotZ;
	float posX;
	bool isMinScale;

	//Mesh * mesh1;
	//Mesh * mesh2;
	
	Material * mat1;

	Camera * camera;

	Input * input;

	Node * chuckNorris;
	Node * theCamarografo;
	Node * theAbuelo;
	Node * thePadre;
	Node * theHijo;

protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	void OnDraw() override;
public:
	Game();
	~Game();
};


