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

	/*Mesh*/
	mat1 = new Material();
	unsigned int programID = mat1->LoadShaders("VertexTexture.glsl", "FragmentTexture.glsl");

	mesh1 = new Mesh(render, "Arma.fbx");
	mesh1->SetMaterial(mat1);
	mesh1->LoadMaterial("ArmaTex.bmp");
	mesh1->SetPos(0, 0, 0);
	mesh1->SetScale(0.01f, 0.01f, 0.01f);

	cout << "Game::OnStart()" << endl;
	return true;
}

bool Game::OnStop() {
	cout << "Game::OnStop()" << endl;

	return true;
}

bool Game::OnUpdate() {
	input->PollEvents();
	i++;
	CollisionManager::GetInstance()->UpdatePhysicsBox();
/*Mesh Transforms*/
	mesh1->Rotate(0, deltaTime, 0);
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
}

Game::Game() {
}


Game::~Game() {
}