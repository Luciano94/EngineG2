#include "Game.h"

bool Game::OnStart() {
	/*velocity of the objects*/
	speed = 30.0f;

	/*Collision Manager*/
	CollisionManager * instance = CollisionManager::GetInstance();	

	/*Input*/
	input = Input::getInstance();
	input->SetWindowContext(window);
	
	/*Camera*/
	camera = new Camera(render);

	/*nodes*/
	chuckNorris = new Node(render); //Scene node
	cameraNode = new Node(render); //Camera

	weaponsNode = new Node(render);
	mFourNode = new Node(render);
	rifleNode = new Node(render);
	pistolNode = new Node(render);

	/*creo la jerarquia*/
	chuckNorris->addChild(cameraNode);
	chuckNorris->addChild(mFourNode);

	/*cargo los modelos*/
	cameraNode->addComponent(camera);
	MeshLoader::GetInstance()->LoadMesh("Assets/sceneDefault.fbx", "Assets/ArmaTex.bmp", chuckNorris, render, camera);
	mFourNode->SetScale(0.5F, 0.5F, 0.5F);
	camera->Translate(glm::vec3(0.0f,0.0f,-500.0f));
	rifleNode = chuckNorris->getNode(3);

	setScene(chuckNorris);
	cout << "Game::OnStart()" << endl;
	return true;
}

bool Game::OnStop() {
	cout << "Game::OnStop()" << endl;
	delete rifleNode;
	delete mFourNode;
	delete weaponsNode;
	delete cameraNode;
	delete chuckNorris;
	delete camera;

	return true;
}

bool Game::OnUpdate() {
	input->PollEvents();

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

	if (input->isInput(GLFW_KEY_J))
		rifleNode->Translate(speed * deltaTime, 0, 0);

	if (input->isInput(GLFW_KEY_K))
		rifleNode->Translate(speed * deltaTime * -1, 0,0);

/*NODE ROTATIONS */

		chuckNorris->Rotate(0, 0, deltaTime);

		rifleNode->Rotate(deltaTime * -1, 0, 0);


/*Translations*/
	if (input->isInput(GLFW_KEY_W))
		camera->Translate(glm::vec3(0, 0, speed * deltaTime));

	if (input->isInput(GLFW_KEY_S))
		camera->Translate(glm::vec3(0, 0, speed * -deltaTime));

	if (input->isInput(GLFW_KEY_A))
		camera->Translate(glm::vec3(speed * deltaTime, 0, 0));

	if (input->isInput(GLFW_KEY_D))
		camera->Translate(glm::vec3(-speed * deltaTime, 0, 0));

	if (input->isInput(GLFW_KEY_LEFT_SHIFT))
		speed = 100.0f;
	else speed = 20.0f;
	return true;
}

void Game::OnDraw()
{
	cout << "Objects Draw = " << render->objectsDraws << endl;
	cout.clear();
	render->objectsDraws = 0;
}

Game::Game() {
}


Game::~Game() {
}