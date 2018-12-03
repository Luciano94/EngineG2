#include "TileMap.h"





TileMap::TileMap( const char * filePath, int winW, int winH, Renderer * render, Material * material){

	LoadLevel(filePath);

	//demas cosas
	scrollX = 0;
	scrollY = 0;

	this->render = render;
	this->material = material;

	Instance = CollisionManager::GetInstance();
	LastCameraPos = CurrentCameraPos = DeltaCameraPos = glm::vec3(0,0,0);

	int tileW = 256 / 4;
	int tileH = 256 / 4;

	viewW = (winW / tileW) + 4;
	viewH = (winH / tileH) + 4;

	Xlvl = viewH;
	Ylvl = viewW;

	view = new vector<vector<int>*>(viewW);
	for (int i = 0; i < viewW; i++)
		view->at(i) = new vector<int>(viewH);

	viewSprite = new vector<vector<Tile*>*>(viewW);
	for (int i = 0; i < viewW; i++)
		viewSprite->at(i) = new vector<Tile*>(viewH);
	ChargeSprite();
	LoadView();
}

void TileMap::LoadLevel(const char * filePath){
	//cargar archivo;
	string buffer;
	ifstream file(filePath);
	lvlW = 1;
	lvlH = 1;
	getline(file, buffer);
	for (int i = 0; i < buffer.length(); i++) {
		if (buffer[i] == ',')
			lvlW++;
	}
	while (getline(file, buffer)) {
		lvlH++;
	}
	file.clear();
	file.seekg(0, std::ios::beg);

	level = new vector<vector<int>*>(lvlW);
	for (int i = 0; i < lvlW; i++) {
		level->at(i) = new vector<int>(lvlH);
	}
	if (file.is_open()) {
		for (int i = 0; i < lvlW; i++) {
			getline(file, buffer);
			int levelW = 0;
			for (int j = 0; j < buffer.length(); j++) {
				switch (buffer[j]) {
				case '0':
					level->at(i)->at(levelW) = 1;
					levelW++;
					break;
				case '1':
					level->at(i)->at(levelW) = 0;
					levelW++;
					break;
				}
			}
		}
	}
	file.close();
}

void TileMap::ChargeSprite() {
	for (int i = 0; i < viewW; i++){
		for (int j = 0; j < viewH; j++){
			viewSprite->at(i)->at(j) = new Tile(render, 1, 1);
			viewSprite->at(i)->at(j)->SetMaterial(material);
			viewSprite->at(i)->at(j)->SetBoundingBox(2.0f, 2.0f, true, 0);
			viewSprite->at(i)->at(j)->AddTexture("Empty.bmp");
			viewSprite->at(i)->at(j)->AddTexture("Pastito.bmp");
		}
	}
}

TileMap::~TileMap() {
	/*delete[] View;
	for (int i = 0; i < viewW; i++) {
		delete[] viewSprite->at(i);
	}*/
}

void TileMap::LoadView() {
	int posx = -12;
	int posy = 9;
	lastposX = 0;
	lastposY = 0;
	for (int i = 0; i < lvlW; i++) {
		posx = -12;
		for (int j = 0; j < lvlH; j++) {
			if (i < viewW && j < viewH) {
				view->at(i)->at(j) = level->at(i)->at(j);
				if (view->at(i)->at(j) == 0) {
					viewSprite->at(i)->at(j)->ChangeTexture(0);
					Instance->SingUpToList(Layers::BckTile, viewSprite->at(i)->at(j));
				}
				if (view->at(i)->at(j) == 1) {
					viewSprite->at(i)->at(j)->ChangeTexture(1);
					Instance->SingUpToList(Layers::CollisionTile, viewSprite->at(i)->at(j));
				}
				posx += 2;
				viewSprite->at(i)->at(j)->SetPos(posx, posy, 0);
			}
		}
		posy -= 2;
	}
}



void TileMap::UpdateViewX() {
	int posx = 10;
	int posy = 9;

	//Update X
	for (int i = 0; i < viewW; i++) {
		for (int j = 1; j < viewH; j++){
			view->at(i)->at(j-1) = view->at(i)->at(j);
		}
	}
	for (int i = 0; i < viewW; i++) {
		int pos = level->at(i)->at(Xlvl);
		view->at(i)->at(viewH - 1) = pos;
	}
	//volver a dibujar
	posx = 12;
	for (int j = 0; j < viewW; j++) {
		if (view->at(j)->at(viewH-1) == 0) {
			viewSprite->at(j)->at(lastposX)->ChangeTexture(0);
			Instance->SingUpToList(Layers::BckTile, viewSprite->at(j)->at(lastposX));
		}
		if (view->at(j)->at(viewH - 1) == 1) {
			viewSprite->at(j)->at(lastposX)->ChangeTexture(1);
			Instance->SingUpToList(Layers::CollisionTile, viewSprite->at(j)->at(lastposX));
		}
		viewSprite->at(j)->at(lastposX)->SetPos(posx + LastCameraPos.x, posy, 0);
		posy -= 2;
	}
	if (lastposX < viewH-1) lastposX++;
	else lastposX = 0;
}

void TileMap::UpdateViewXReverse() {
}

void TileMap::UpdateViewY() {
	int posx = 12;
	int posy = 9;
	//Update Y
	for (int i = 1; i < viewW; i++) {
		for (int j = 0; j < viewH; j++) {
			view->at(i - 1)->at(j) = view->at(i)->at(j);
		}
	}
	for (int i = 0; i < viewH; i++) {
		int pos = level->at(i)->at(Ylvl);
		view->at(viewW - 1)->at(i) = pos;
	}
	//volver a dibujar
	for (int j = 0; j < viewH; j++) {
		if (view->at(viewW - 1)->at(j) == 0) {
			viewSprite->at(lastposY)->at(j)->ChangeTexture(0);
			Instance->SingUpToList(Layers::BckTile, viewSprite->at(lastposY)->at(j));
		}
		if (view->at(viewW - 1)->at(j) == 1) {
			viewSprite->at(lastposY)->at(j)->ChangeTexture(1);
			Instance->SingUpToList(Layers::CollisionTile, viewSprite->at(lastposY)->at(j));
		}
		viewSprite->at(lastposY)->at(j)->SetPos(posx, posy + CurrentCameraPos.y, 0);
		posy -= 2;
	}
	if (lastposY < viewH - 1) lastposY++;
	else lastposY = 0;
}

void TileMap::UpdateViewYReverse()
{
}

void TileMap::Draw(){
	for (int i = 0; i < viewW; i++) {
		for (int j = 0; j < viewH; j++) {
			viewSprite->at(i)->at(j)->Draw();
		}
	}
}


void TileMap::Update(){
	//Calculate deltaCamera
	CurrentCameraPos = render->getCameraPos();
	DeltaCameraPos =  CurrentCameraPos - LastCameraPos;
	LastCameraPos = CurrentCameraPos;
	//UpdateX
	scrollX += DeltaCameraPos.x;
	if (scrollX >= 2) {
		if (Xlvl < lvlW - 1)Xlvl++;
		UpdateViewX();
		scrollX = 0;
	}else
	if (scrollX <= -2) {
		if (Xlvl < 0)Xlvl--;
		UpdateViewX();
		scrollX = 0;
	}
	//UpdateY
	scrollY += DeltaCameraPos.y;
	if (scrollY <= -2) {
		if (Ylvl < 0)Ylvl--;
		UpdateViewY();
		scrollY = 0;
	}else
		if (scrollY >= 2) {
			if (Ylvl > lvlH - 1)Ylvl++;
			UpdateViewY();
			scrollY = 0;
		}
}