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
	weaponsNode = new Node(render);
	mFourNode = new Node(render);
	cameraNode = new Node(render);
	rifleNode = new Node(render);
	pistolNode = new Node(render);

	/*creo la jerarquia*/
	chuckNorris->addChild(cameraNode);
	chuckNorris->addChild(mFourNode);
	//chuckNorris->addChild(pistolNode);
	//weaponsNode->addChild(mFourNode);
	//mFourNode->addChild(rifleNode);

	/*cargo los modelos*/
	cameraNode->addComponent(camera);
	Importer::LoadMesh("Definitivo.fbx", "Sample2.bmp", mFourNode, render, camera);
	camera->Translate(glm::vec3(0.0f,0.0f,-10.0f));
	rifleNode = mFourNode->getNode(5);
	//Importer::LoadMesh("Arma.fbx", "ArmaTex.bmp", mFourNode, render, camera);
	//Importer::LoadMesh("Arma2.fbx", "ArmaTex2.bmp", rifleNode, render, camera);
	//Importer::LoadMesh("weapon.fbx", "weapon.bmp", pistolNode, render, camera);

	/*seteo la escala y posicion*/
	//chuckNorris->SetPos(0, 0, 0);
	//mFourNode->SetScale(0.5f, 0.5f, 0.5f);
	//mFourNode->SetPos(0, 0, -10);
	//rifleNode->SetScale(10, 10, 10);

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
	//i++;
	//CollisionManager::GetInstance()->UpdatePhysicsBox();

/*Node Transforms*/
	//Roto al cargador del arma
	//mFourNode->getNode(1)->Rotate(0, deltaTime, 0);
	//Roto el cuerpo del arma
	//mFourNode->Rotate(deltaTime, 0, 0);
	//roto la pistola y sus nodos
	//pistolNode->Rotate(0, deltaTime, 0);

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