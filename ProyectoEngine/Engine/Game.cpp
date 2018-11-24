#include "Game.h"

bool Game::OnStart() {
	i = 0;
	speed = 2;
	CollisionManager * instance = CollisionManager::GetInstance();
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
	/*spr1 = new Sprite(render);
	spr1->SetMaterial(mat2);
	spr1->LoadMaterial("sample2.bmp");
	spr1->SetBoundingBox(2.0f, 2.0f, true);
	instance->SingUpToList(Layers::Player, spr1);*/
	/*Sprite 2*/
	spr2 = new Sprite(render,4,2);
	spr2->SetMaterial(mat2);
	spr2->LoadMaterial("SpriteSheet.bmp");
	spr2->SetPos(0, 10, 0);
	spr2->SetBoundingBox(2.0f, 2.0f, false, 10);
	instance->SingUpToList(Layers::Enemy, spr2);
	spr2->SetAnim(0, 7, 0.1f);
	/*Sprite 3*/
	spr3 = new Sprite(render, 1, 1);
	spr3->SetMaterial(mat2);
	spr3->LoadMaterial("sample2.bmp");
	spr3->SetPos(0, -10, 0);
	spr3->SetBoundingBox(2.0f, 2.0f, false, 80);
	instance->SingUpToList(Layers::EnemyBullet, spr3);
	/*Sprite 4*/
	spr4 = new Sprite(render, 1, 1);
	spr4->SetMaterial(mat2);
	spr4->LoadMaterial("sample2.bmp");
	spr4->SetPos(10, 0, 0);
	spr4->SetBoundingBox(2.0f, 2.0f, false, 10);
	instance->SingUpToList(Layers::EnemyBullet, spr4);
	/*Sprite 5*/
	spr5 = new Sprite(render, 1, 1);
	spr5->SetMaterial(mat2);
	spr5->LoadMaterial("sample2.bmp");
	spr5->SetPos(-10, 0, 0);
	spr5->SetBoundingBox(2.0f, 2.0f, false, 10);
	instance->SingUpToList(Layers::Enemy, spr5);
	//cout << "Game::OnStart()" << endl;
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
	//delete spr1;
	delete spr2;
	delete spr3;
	delete spr4;
	delete spr5;
	delete cir1;
	return true;
}

bool Game::OnUpdate() {
	i++;
	CollisionManager::GetInstance()->UpdatePhysicsBox();
	/*Animations*/
	spr2->UpdAnim(deltaTime);
	/*Translate*/
	tr1->Rotate(0, 0, speed * deltaTime);
	tr2->Translate(speed * deltaTime, 0, 0);
	sqr1->Translate(speed * deltaTime * -1, 0, 0);
	cir1->Translate(0, speed * deltaTime, 0);
	spr2->Translate(0,-speed *  deltaTime, 0);
	spr3->Translate(0, speed * deltaTime , 0);
	spr4->Translate(-speed * deltaTime * 2.0f,0, 0);
	spr5->Translate( speed * deltaTime,0, 0);
	//cout <<"Game::OnUpdate():"<< i <<endl;
	return true;
}

void Game::OnDraw()
{
	/*tr1->Draw();
	tr2->Draw();
	sqr1->Draw();
	cir1->Draw();*/
	//spr1->Draw();
	spr2->Draw();
	spr3->Draw();
	spr5->Draw();
	spr4->Draw();
	//cout << "Game::OnDraw(): " << i << endl;
}

Game::Game() {
}


Game::~Game() {
}