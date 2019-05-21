#include "Game.h"

bool Game::OnStart() {
	/*velocity of the objects*/
	speed = 20.0f;

	/*Collision Manager*/
	CollisionManager * instance = CollisionManager::GetInstance();	

	/*Input*/
	input = Input::getInstance();
	input->SetWindowContext(window);
	
	/*Camera*/
	camera = new Camera(render);

	/*Mesh 1*/
	mesh1 = new Mesh(render, "Arma2.fbx", "ArmaTex2.bmp");
	mesh1->SetPos(0, 0, 0);
	mesh1->SetRot(0, 0, 90);
	/*Mesh 2*/
	mesh2 = new Mesh(render, "Arma.fbx", "ArmaTex.bmp");
	mesh2->SetPos(10, 0, 0);
	mesh2->SetScale(0.05f, 0.05f, 0.05f);

	cout << "Game::OnStart()" << endl;
	return true;
}

bool Game::OnStop() {
	cout << "Game::OnStop()" << endl;
	delete mat1;
	delete mesh1;
	delete mesh2;
	delete camera;
	return true;
}

bool Game::OnUpdate() {
	input->PollEvents();
	i++;
	CollisionManager::GetInstance()->UpdatePhysicsBox();
/*Mesh Transforms*/
	mesh1->Rotate(0, deltaTime, 0);
	mesh2->Rotate(0, deltaTime, 0);
/*Rotations*/
	if (input->isInput(GLFW_KEY_Q))
		camera->Rotate(glm::vec3(0, 0, deltaTime));

	if (input->isInput(GLFW_KEY_E))
		camera->Rotate(glm::vec3(0, 0, -deltaTime));

	if (input->isInput(GLFW_KEY_UP))
		camera->Rotate(glm::vec3(0, -deltaTime, 0));

	if (input->isInput(GLFW_KEY_DOWN))

		camera->Rotate(glm::vec3(0,  deltaTime, 0));
	if (input->isInput(GLFW_KEY_LEFT))
		camera->Rotate(glm::vec3( deltaTime,0, 0));

	if (input->isInput(GLFW_KEY_RIGHT))
		camera->Rotate(glm::vec3(  -deltaTime,0, 0));

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
	mesh1->Draw();
	mesh2->Draw();
}

Game::Game() {
}


Game::~Game() {
}