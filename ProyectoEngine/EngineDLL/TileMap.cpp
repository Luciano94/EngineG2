#include "TileMap.h"





TileMap::TileMap( const char * filePath, int winW, int winH, Renderer * render, Material * material){
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
		for (int i = 0; i < lvlW; i++){
			getline(file, buffer);
			int levelW = 0;
			for (int j = 0; j < buffer.length(); j++){
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
	View = new int[viewW, viewH];
	Xlvl = viewW;
	Ylvl = viewH;

	view = new vector<vector<int>*>(viewW);
	for (int i = 0; i < viewW; i++)
		view->at(i) = new vector<int>(viewH);

	viewSprite = new vector<vector<Tile*>*>(viewW);
	for (int i = 0; i < viewW; i++)
		viewSprite->at(i) = new vector<Tile*>(viewH);
	ChargeSprite();
	LoadView();
}

void TileMap::ChargeSprite() {
	for (int i = 0; i < viewW; i++){
		for (int j = 0; j < viewH; j++){
			viewSprite->at(i)->at(j) = new Tile(render, 1, 1);
			viewSprite->at(i)->at(j)->SetMaterial(material);
			viewSprite->at(i)->at(j)->SetBoundingBox(2.0f, 2.0f, true, 0);
			viewSprite->at(i)->at(j)->AddTexture("Empty.bmp");
			viewSprite->at(i)->at(j)->AddTexture("Sample2.bmp");
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
	for (int i = 0; i < lvlW; i++) {
		posx = -12;
		for (int j = 0; j < lvlH; j++) {
			if (i < viewW && j < viewH) {
				int offsetX = j + CurrentCameraPos.x;
				int offsetY = i + CurrentCameraPos.y;
				if (offsetX >= lvlW) offsetX = lvlW - 1;
				if (offsetY >= lvlH) offsetY = lvlH - 1;
				int pos = level->at(offsetX)->at(offsetY);
				View[i, j] = level->at(i)->at(j);
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

void TileMap::UpdateView() {
	int posx = 10;
	int posy = 9;
	//Update X
	for (int i = 0; i < viewW; i++) {
		for (int j = 1; j < viewH; j++){
			view->at(i)->at(j-1) = view->at(i)->at(j);
		}
	}
	//volver a dibujar
		posx = 10;
		for (int j = 0; j < viewW; j++) {
			if (view->at(j)->at(viewH-1) == 0) {
				viewSprite->at(j)->at(lastposX)->ChangeTexture(0);
				Instance->SingUpToList(Layers::BckTile, viewSprite->at(j)->at(lastposX));
			}
			if (view->at(j)->at(viewH - 1) == 1) {
				viewSprite->at(j)->at(lastposX)->ChangeTexture(1);
				Instance->SingUpToList(Layers::CollisionTile, viewSprite->at(j)->at(lastposX));
			}
			viewSprite->at(j)->at(lastposX)->SetPos(posx + CurrentCameraPos.x, posy, 0);
			posy -= 2;
		}
		if (lastposX < viewW) lastposX++;
		else lastposX = 0;

}

void TileMap::Draw(){
	for (int i = 0; i < viewW; i++) {
		for (int j = 0; j < viewH; j++) {
			viewSprite->at(i)->at(j)->Draw();
		}
	}
}


void TileMap::Update(){
	CurrentCameraPos = render->getCameraPos();
	DeltaCameraPos =  CurrentCameraPos - LastCameraPos;
	LastCameraPos = CurrentCameraPos;
	scrollX += DeltaCameraPos.x;
	if (scrollX >= 2) {
		if (Ylvl < lvlH - 1)Ylvl++;
		Instance->ClearLayer(Layers::CollisionTile);
		Instance->ClearLayer(Layers::BckTile);
		UpdateView();
		scrollX = 0;
	}
	scrollY += DeltaCameraPos.y;
	if (scrollY >= 1) {
		if (Ylvl < lvlH - 1)Ylvl++;
		Instance->ClearLayer(Layers::CollisionTile);
		Instance->ClearLayer(Layers::BckTile);
		UpdateView();
		scrollY = 0;
	}
}