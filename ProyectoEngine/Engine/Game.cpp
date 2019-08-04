#include "Game.h"

bool Game::OnStart() {
	/*init the game*/
	gameStart = false;

	/*velocity of the objects*/
	speed = 20.0f;
	textTime = 3.0f;

	/*Input*/
	input = Input::getInstance();
	input->SetWindowContext(window);

	/*Collision Manager*/
	CollisionManager * instance = CollisionManager::GetInstance();
	
	/*Material*/
	mat1 = new Material();
	unsigned int programID = mat1->LoadShaders("VertexTexture.glsl", "FragmentTexture.glsl");

	/*Collider Tiles*/
	vector<int> * colliderTiles = new vector<int>();
	colliderTiles->push_back(3);
	colliderTiles->push_back(8);

	/*Tileset*/
	tilesito = new Tilemap(render, 11.0f, 201.0f, "mapv3.csv", 4, 4, 12, 2, colliderTiles);
	tilesito->SetMaterial(mat1);
	tilesito->LoadTexture("mapv3.bmp");
	
	/*Player*/
	player = new Sprite(render, 3, 1);
	player->SetMaterial(mat1);
	player->LoadMaterial("PlayerRun.bmp");
	player->SetPos(0, 0, 0);
	player->SetBoundingBox(2.0f, 2.0f, false, 20);
	instance->SingUpToList(Layers::Player, player);
	player->SetAnim(0, 2, 0.1f);

	/*StartCount*/
	startCount = new Sprite(render, 2, 3);
	startCount->SetMaterial(mat1);
	startCount->LoadMaterial("StartCount.bmp");
	startCount->SetPos(0, 1, 0);
	startCount->SetAnim(0, 4, 1.0f);

	/*WinText*/
	winText = new Sprite(render, 1, 2);
	winText->SetMaterial(mat1);
	winText->LoadMaterial("WinLoseText.bmp");
	winText->SetPos(0, 100, 0);
	winText->SetAnim(1, 1, 1.0f);

	/*LoseText*/
	loseText = new Sprite(render, 1, 2);
	loseText->SetMaterial(mat1);
	loseText->LoadMaterial("WinLoseText.bmp");
	loseText->SetPos(0, 100, 0);
	loseText->SetAnim(2, 2, 1.0f);

	/*Obstacle*/
	obstacle = new Sprite(render, 1, 1);
	obstacle->SetMaterial(mat1);
	obstacle->LoadMaterial("Obstacle.bmp");
	obstacle->SetPos(0, -100, 0);
	obstacle->SetBoundingBox(2.0f, 2.0f, false, 50);
	instance->SingUpToList(Layers::Enemy, obstacle);

	/*Obstacle*/
	obstacle1 = new Sprite(render, 1, 1);
	obstacle1->SetMaterial(mat1);
	obstacle1->LoadMaterial("Obstacle.bmp");
	obstacle1->SetPos(-3, -200, 0);
	obstacle1->SetBoundingBox(2.0f, 2.0f, false, 50);
	instance->SingUpToList(Layers::Enemy, obstacle1);

	/*Obstacle*/
	obstacle2 = new Sprite(render, 1, 1);
	obstacle2->SetMaterial(mat1);
	obstacle2->LoadMaterial("Obstacle.bmp");
	obstacle2->SetPos(4, -300, 0);
	obstacle2->SetBoundingBox(2.0f, 2.0f, false, 50);
	instance->SingUpToList(Layers::Enemy, obstacle2);
	
	cout << "Game::OnStart()" << endl;
	return true;
}

void Game::showWin() {
	gameFinish = true;
	winText->SetPos(0,player->GetPos().y,0);
	if (textTime > 0.0f) {
		winText->UpdAnim(deltaTime);
		winText->Draw();
		textTime -= deltaTime;
	}
	else {
		window->Stop();
	}
}

void Game::showLose() {
	gameFinish = true;
	loseText->SetPos(0,player->GetPos().y,0);
	if (textTime > 0.0f) {
		loseText->UpdAnim(deltaTime);
		loseText->Draw();
		textTime -= deltaTime;
	}
	else {
		window->Stop();
	}

}

bool Game::resolveTileCollision() {
	int result = tilesito->NextTileIsCollider(player->GetPos().x, player->GetPos().y, 2.0f, 2.0f);

	switch (result)
	{
	case -1:
		return true;
	case 0:
		showWin();
		break;
	case 1:
		showLose();
		break;
	}
	return false;
}

void Game::PlayerMovment() {
	if (resolveTileCollision()) {
		player->Translate(glm::vec3(0, -speed * deltaTime, 0));
	}


	if (input->isInput(GLFW_KEY_A)) {
		if (resolveTileCollision()) {
			player->Translate(glm::vec3(-speed * deltaTime, 0, 0));
		}
	}

	if (input->isInput(GLFW_KEY_D)) {
		if (resolveTileCollision()) {
			player->Translate(glm::vec3(speed * deltaTime, 0, 0));
		}
	}
}

void Game::CameraMovment(glm::vec3 playerPos) {
	glm::vec3 newPos(render->getCameraPos().x, playerPos.y, render->getCameraPos().z);
	render->setCameraPos(newPos);
}

bool Game::OnStop() {
	cout << "Game::OnStop()" << endl;
	delete mat1;
	delete player;
	delete tilesito;
	delete obstacle;
	delete obstacle1;
	delete obstacle2;
	delete winText;
	delete loseText;
	
	return true;
}

bool Game::OnUpdate() {
	CollisionManager::GetInstance()->UpdatePhysicsBox();

	/*Game Logic*/
	if (startCount->UpdAnim(deltaTime) == 4)
		gameStart = true;

	if (gameStart) {
		player->UpdAnim(deltaTime);
		PlayerMovment();
		CameraMovment(player->GetPos());
	}

	return true;
}

void Game::OnDraw()
{
	tilesito->Draw();
	player->Draw();

	if (!gameFinish) {
		obstacle->Draw();
		obstacle1->Draw();
		obstacle2->Draw();
	}
	else {
		render->ClearScreen();
		winText->Draw();
		loseText->Draw();
	}
	if(!gameStart)
		startCount->Draw();
}

Game::Game() {
}


Game::~Game() {
}