#include "Game.h"

bool Game::OnStart() {
	i = 0;
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