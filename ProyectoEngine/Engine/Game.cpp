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

	/*nodes*/
	chuckNorris = new Node(render);
	theAbuelo = new Node(render);
	thePadre = new Node(render);
	theCamarografo = new Node(render);
	theCamarografo->addComponent(camera);
	chuckNorris->addChild(theCamarografo);
	chuckNorris->addChild(theAbuelo);
	//theHijo = new Node(render);
	/*creo la jerarquia*/
	theAbuelo->addChild(thePadre);
	//thePadre->addChild(theHijo);
	/*cargo los modelos*/
	Importer::LoadMesh("Arma.fbx", "ArmaTex.bmp", thePadre, render);
	//Importer::LoadMesh("Arma2.fbx", "ArmaTex2.bmp", theHijo, render);
	/*seteo la escala y posicion*/
	thePadre->SetScale(0.05f, 0.05f, 0.05f);
	//theHijo->SetScale(15, 15, 15);
	thePadre->SetPos(0, 0, -10);

	setScene(chuckNorris);
	cout << "Game::OnStart()" << endl;
	return true;
}

bool Game::OnStop() {
	cout << "Game::OnStop()" << endl;
	//delete theHijo;
	delete thePadre;
	delete theAbuelo;
	return true;
}

bool Game::OnUpdate() {
	input->PollEvents();
	i++;
	CollisionManager::GetInstance()->UpdatePhysicsBox();
/*Node Transforms*/
	theAbuelo->Rotate(0, 0, deltaTime);
	thePadre->getNode(1)->Rotate(0, deltaTime, 0);
	thePadre->Rotate(deltaTime, 0, 0);
	//theHijo->Rotate(deltaTime, 0, 0);
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
	//thePadre->Draw();
	//cout << thePadre->getComponent(1)->type << endl;
	//theHijo->Draw();
}

Game::Game() {
}


Game::~Game() {
}