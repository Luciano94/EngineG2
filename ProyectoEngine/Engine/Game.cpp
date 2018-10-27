#include "Game.h"

bool Game::OnStart() {
	i = 0;
	speed = 1;
	/*TRIANGULO 1*/
	mat1 = new Material();
	unsigned int programID = mat1->LoadShaders("vertexshader.txt", "fragmentshader.txt");
	tr1 = new Triangle(render);
	tr1->SetMaterial(mat1);
	/*TRIANGULO 2*/
	tr2 = new Triangle(render);
	tr2->SetMaterial(mat1);
	/*CUADRADO*/
	mat3 = new Material();
	unsigned int ProgramID3 = mat3->LoadShaders("vColor.glsl", "fColor.glsl");
	sqr1 = new Square(render);
	sqr1->SetMaterial(mat3);
	/*Circulo*/
	cir1 = new Circle(render,1,20);
	cir1->SetMaterial(mat3);
	/*Sprite*/
	mat2 = new Material();
	unsigned int programID2 = mat2->LoadShaders("VertexTexture.glsl", "FragmentTexture.glsl");
	spr1 = new Sprite(render);
	spr1->SetMaterial(mat2);
	spr1->LoadMaterial("sample2.bmp");
	cout << "Game::OnStart()" << endl;
	return true;
}

bool Game::OnStop() {
	cout << "Game::OnStop()" << endl;
	delete mat1;
	delete mat2;
	delete mat3;
	delete tr1;
	delete tr2;
	delete sqr1;
	delete spr1;
	delete cir1;
	return true;
}

bool Game::OnUpdate() {
	i++;
	tr1->Rotate(0, 0, speed * deltaTime);
	tr2->Translate(speed * deltaTime, 0, 0);
	sqr1->Translate(speed * deltaTime * -1, 0, 0);
	cir1->Translate(0, speed * deltaTime, 0);
	cout <<"Game::OnUpdate():"<< i <<endl;
	return true;
}

void Game::OnDraw()
{
	tr1->Draw();
	tr2->Draw();
	sqr1->Draw();
	cir1->Draw();
	spr1->Draw();
	cout << "Game::OnDraw(): " << i << endl;
}

Game::Game() {
}


Game::~Game() {
}