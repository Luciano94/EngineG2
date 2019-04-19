#include "Game.h"

bool Game::OnStart() {
	/*velocity of the objects*/
	speed = 2.0f;

	/*Collision Manager*/
	CollisionManager * instance = CollisionManager::GetInstance();
	
	/*Material*/
	mat1 = new Material();
	unsigned int programID = mat1->LoadShaders("VertexTexture.glsl", "FragmentTexture.glsl");

	/*Tileset*/
	tilesito = new TileMap("MatrixLevel.csv", 800, 600, render, mat1);
	/*Input*/
	input = Input::getInstance();
	input->SetWindowContext(window);
	/*Sprite 1*/	
	spr1 = new Sprite(render, 8, 8);
	spr1->SetMaterial(mat1);
	spr1->LoadMaterial("asteroid.bmp");
	spr1->SetPos(0, 0, 0);
	spr1->SetBoundingBox(2.0f, 2.0f, false, 10);
	instance->SingUpToList(Layers::Player, spr1);
	spr1->SetAnim(0, 63, 0.1f);
	
	/*Sprite 2*/
	spr2 = new Sprite(render, 4, 2);
	spr2->SetMaterial(mat1);
	spr2->LoadMaterial("SpriteSheet.bmp");
	spr2->SetPos(0, 0, 0);
	spr2->SetBoundingBox(2.0f, 2.0f, false, 20);
	instance->SingUpToList(Layers::Player, spr2);
	spr2->SetAnim(0, 7, 0.1f);
	
	/*Sprite 3*/
	spr3 = new Sprite(render, 1, 1);
	spr3->SetMaterial(mat1);
	spr3->LoadMaterial("sample2.bmp");
	spr3->SetPos(10,0, 0);
	spr3->SetBoundingBox(2.0f, 2.0f, false, 100);
	instance->SingUpToList(Layers::EnemyBullet, spr3);
	
	/*Camera*/
	camera = new Camera(render);

	cout << "Game::OnStart()" << endl;
	return true;
}

bool Game::OnStop() {
	cout << "Game::OnStop()" << endl;
	delete mat1;

	delete spr1;
	delete spr2;
	delete spr3;
	
	return true;
}

bool Game::OnUpdate() {
	input->PollEvents();
	i++;
	CollisionManager::GetInstance()->UpdatePhysicsBox();
	tilesito->Update();
	/*Animations*/
	spr2->UpdAnim(deltaTime);
	spr1->UpdAnim(deltaTime);
	/*Translations*/
	if(!tilesito->CheckCollisions(spr2->getBoundingBox(), Directions::Down))
		spr2->Translate(0,-speed* deltaTime, 0);
	if (!tilesito->CheckCollisions(spr2->getBoundingBox(), Directions::Left))
		spr2->Translate(speed * deltaTime,0, 0);
	spr3->Translate(-speed * deltaTime ,0, 0);
	
	/*Rotations*/
	if (input->isInput(GLFW_KEY_Q))
		camera->Rotate(glm::vec3(0, 0, speed * deltaTime));

	if (input->isInput(GLFW_KEY_E))
		camera->Rotate(glm::vec3(0, 0, speed * -deltaTime));

	if (input->isInput(GLFW_KEY_UP))
		camera->Rotate(glm::vec3(0,speed * -deltaTime, 0));

	if (input->isInput(GLFW_KEY_DOWN))

		camera->Rotate(glm::vec3(0, speed * deltaTime, 0));
	if (input->isInput(GLFW_KEY_LEFT))
		camera->Rotate(glm::vec3( speed * deltaTime,0, 0));

	if (input->isInput(GLFW_KEY_RIGHT))
		camera->Rotate(glm::vec3( speed * -deltaTime,0, 0));

/*Translations*/
	if (input->isInput(GLFW_KEY_W))
		camera->Translate(glm::vec3(0, 0, speed * deltaTime));

	if (input->isInput(GLFW_KEY_S))
		camera->Translate(glm::vec3(0, 0, speed * -deltaTime));

	if (input->isInput(GLFW_KEY_A))
		camera->Translate(glm::vec3(speed * deltaTime, 0, 0));

	if (input->isInput(GLFW_KEY_D))
		camera->Translate(glm::vec3(-speed * deltaTime, 0, 0));
	return true;
}

void Game::OnDraw()
{
	tilesito->Draw();
	spr1->Draw();
	spr2->Draw();
	spr3->Draw();
}

Game::Game() {
}


Game::~Game() {
}