#include "Game.h"

bool Game::OnStart() {
	i = 0;
	speed = 1;
	rotZ = 0;
	posX = 0;
	/*TRIANGULO 1*/
	mat1 = new Material();
	unsigned int programID = mat1->LoadShaders("vertexshader.txt", "fragmentshader.txt");
	tr1 = new Triangle(render);
	tr1->SetMaterial(mat1);
	/*TRIANGULO 2*/
	mat2 = new Material();
	unsigned int programID2 = mat2->LoadShaders("vertexshader.txt", "fragmentshader.txt");
	tr2 = new Triangle(render);
	tr2->SetMaterial(mat2);
	/*CUADRADO*/
	mat3 = new Material();
	unsigned int ProgramID3 = mat3->LoadShaders("vColor.glsl", "fColor.glsl");
	//unsigned int ProgramID3 = mat3->LoadShaders("vertexshader.txt", "fragmentshader.txt");
	sqr1 = new Square(render);
	sqr1->SetMaterial(mat3);
	cout << "Game::OnStart()" << endl;
	return true;
}

bool Game::OnStop() {
	cout << "Game::OnStop()" << endl;
	return true;
}

bool Game::OnUpdate() {
	i++;
	rotZ += deltaTime * speed;
	posX += deltaTime * speed;
	tr1->SetRot(0, 0, rotZ);
	tr2->SetPos(posX, 0, 0);
	sqr1->SetPos(-posX, 0, 0);
	cout <<"Game::OnUpdate():"<< i <<endl;
	return true;
}

void Game::OnDraw()
{
	tr1->Draw();
	tr2->Draw();
	sqr1->Draw();
	cout << "Game::OnDraw(): " << i << endl;
}

Game::Game() {
}


Game::~Game() {
}