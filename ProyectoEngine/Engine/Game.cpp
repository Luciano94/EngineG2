#include "Game.h"

bool Game::OnStart() {
	/*velocity of the objects*/
	speed = 20.0f;

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
	tilesito = new Tilemap(render, 11.0f, 201.0f, "mapv3.csv", 4, 4, 10, 2, colliderTiles);
	tilesito->SetMaterial(mat1);
	tilesito->LoadTexture("mapv3.bmp");
	
	/*Sprite 2*/
	player = new Sprite(render, 3, 1);
	player->SetMaterial(mat1);
	player->LoadMaterial("PlayerRun.bmp");
	player->SetPos(0, 0, 0);
	player->SetBoundingBox(2.0f, 2.0f, false, 20);
	instance->SingUpToList(Layers::Player, player);
	player->SetAnim(0, 2, 0.5f);
	
	cout << "Game::OnStart()" << endl;
	return true;
}


void Game::PlayerMovment() {
	if (tilesito->NextTileIsCollider(player->GetPos().x, player->GetPos().y, 2.0f, 2.0f)) {
		window->Stop();
	}
	else {
		player->Translate(glm::vec3(0, -speed * deltaTime, 0));
	}


	if (input->isInput(GLFW_KEY_A)) {
		if (tilesito->NextTileIsCollider(player->GetPos().x, player->GetPos().y, 2.0f, 2.0f)) {
			window->Stop();
		}
		else {
			player->Translate(glm::vec3(-speed * deltaTime, 0, 0));
		}
	}

	if (input->isInput(GLFW_KEY_D)) {
		if (tilesito->NextTileIsCollider(player->GetPos().x, player->GetPos().y, 2.0f, 2.0f)) {
			window->Stop();
		}
		else {

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

	
	return true;
}

bool Game::OnUpdate() {
	i++;
	CollisionManager::GetInstance()->UpdatePhysicsBox();
	//tilesito->Update();
	/*Animations*/
	player->UpdAnim(deltaTime);
	PlayerMovment();
	CameraMovment(player->GetPos());

	player->UpdAnim(deltaTime);

	/*Translate*/
	//render->CameraTranslate(glm::vec3(speed* deltaTime,0, 0));
	/*if(!tilesito->CheckCollisions(spr2->getBoundingBox(), Directions::Down))
		spr2->Translate(0,-speed* deltaTime, 0);
	if (!tilesito->CheckCollisions(spr2->getBoundingBox(), Directions::Left))
		spr2->Translate(speed * deltaTime,0, 0);
	spr3->Translate(-speed * deltaTime ,0, 0);*/
	
	return true;
}

void Game::OnDraw()
{
	tilesito->Draw();
	player->Draw();

}

Game::Game() {
}


Game::~Game() {
}