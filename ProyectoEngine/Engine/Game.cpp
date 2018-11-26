#include "Game.h"

bool Game::OnStart() {
	i = 0;
	speed = 2;
	CollisionManager * instance = CollisionManager::GetInstance();
	
	/*Material Sprite*/
	mat2 = new Material();
	unsigned int programID2 = mat2->LoadShaders("VertexTexture.glsl", "FragmentTexture.glsl");
	
	/*Sprite 1*/	
	spr1 = new Sprite(render, 8, 8);
	spr1->SetMaterial(mat2);
	spr1->LoadMaterial("asteroid.bmp");
	spr1->SetPos(0, 0, 0);
	spr1->SetBoundingBox(2.0f, 2.0f, false, 100);
	instance->SingUpToList(Layers::Player, spr1);
	spr1->SetAnim(0, 63, 0.1f);
	
	/*Sprite 2*/
	spr2 = new Sprite(render, 4, 2);
	spr2->SetMaterial(mat2);
	spr2->LoadMaterial("SpriteSheet.bmp");
	spr2->SetPos(0, 10, 0);
	spr2->SetBoundingBox(2.0f, 2.0f, false, 20);
	instance->SingUpToList(Layers::Enemy, spr2);
	spr2->SetAnim(0, 7, 0.1f);
	
	/*Sprite 3*/
	spr3 = new Sprite(render, 1, 1);
	spr3->SetMaterial(mat2);
	spr3->LoadMaterial("sample2.bmp");
	spr3->SetPos(0, -10, 0);
	spr3->SetBoundingBox(2.0f, 2.0f, false, 10);
	instance->SingUpToList(Layers::EnemyBullet, spr3);
	
	/*Sprite 4*/
	/*spr4 = new Sprite(render, 1, 1);
	spr4->SetMaterial(mat2);
	spr4->LoadMaterial("sample2.bmp");
	spr4->SetPos(10, 0, 0);
	spr4->SetBoundingBox(2.0f, 2.0f, false, 10);
	instance->SingUpToList(Layers::EnemyBullet, spr4);
	*/
	/*Sprite 5*/
	spr5 = new Sprite(render, 1, 1);
	spr5->SetMaterial(mat2);
	spr5->LoadMaterial("sample2.bmp");
	spr5->SetPos(-10, 0, 0);
	spr5->SetBoundingBox(2.0f, 2.0f, false, 10);
	instance->SingUpToList(Layers::PlayerBullet, spr5);
	
	cout << "Game::OnStart()" << endl;
	return true;
}

bool Game::OnStop() {
	cout << "Game::OnStop()" << endl;

	delete mat2;

	delete spr1;
	delete spr2;
	delete spr3;
	//delete spr4;
	delete spr5;
	
	return true;
}

bool Game::OnUpdate() {
	i++;
	CollisionManager::GetInstance()->UpdatePhysicsBox();
	/*Animations*/
	spr2->UpdAnim(deltaTime);
	spr1->UpdAnim(deltaTime);

	/*Translate*/
	spr2->Translate(0,-speed *  deltaTime, 0);
	spr3->Translate(0, speed * deltaTime , 0);
	//spr4->Translate(-speed * deltaTime * 2.0f,0, 0);
	spr5->Translate( speed * deltaTime,0, 0);
	
	return true;
}

void Game::OnDraw()
{
	spr1->Draw();
	spr2->Draw();
	spr3->Draw();
	spr5->Draw();
	//spr4->Draw();
}

Game::Game() {
}


Game::~Game() {
}