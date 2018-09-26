#include "Game.h"

bool Game::OnStart() {
	i = 0;
	deltaTime = 0;
	mat1 = new Material();
	unsigned int programID = mat1->LoadShaders("vertexshader.txt", "fragmentshader.txt");
	tr1 = new Triangle(render);
	tr1->SetMaterial(mat1);
	cout << "Game::OnStart()" << endl;
	return true;
}

bool Game::OnStop() {
	cout << "Game::OnStop()" << endl;
	return true;
}

bool Game::OnUpdate() {
	i++;
	if (i == 60) {
		i = 0;
		deltaTime++;
	}
	if (deltaTime == 360) {
		deltaTime = 0;
	}
	float z = deltaTime * (180 / 3.141592654);
	tr1->SetRot(0, 0, z);
	cout <<"Game::OnUpdate():"<< i <<endl;
	return true;
}

void Game::OnDraw()
{
	tr1->Draw();
	cout << "Game::OnDraw(): " << i << endl;
}

Game::Game() {
}


Game::~Game() {
}