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
	this->render = render;
	this->material = material;
	Instance = CollisionManager::GetInstance();
	LastCameraPos = CurrentCameraPos = DeltaCameraPos = glm::vec3(0,0,0);
	int tileW = 256 / 4;
	int tileH = 256 / 4;

	viewW = (winW / tileW) + 2;
	viewH = (winH / tileH) + 2;
	View = new int[viewW, viewH];

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
	delete[] View;
	for (int i = 0; i < viewW; i++) {
		delete[] viewSprite->at(i);
	}
}

void TileMap::LoadView() {
	int posx = -10;
	int posy = 9;
	for (int i = 0; i < lvlW; i++){
		posx = -10;
		for (int j = 0; j < lvlH; j++) {
			if (i < viewW && j < viewH) {
				int offsetX = j + CurrentCameraPos.x;
				int offsetY = i + CurrentCameraPos.y;
				if (offsetX >= lvlW) offsetX = lvlW-1;
				if (offsetY >= lvlH) offsetY = lvlH-1;
				int pos = level->at(offsetX)->at(offsetY);
				View[i, j] = pos;
				
				if (View[i, j] == 0) {
					viewSprite->at(i)->at(j)->ChangeTexture(0);
					Instance->SingUpToList(Layers::BckTile, viewSprite->at(i)->at(j));
				}
				if (View[i, j] == 1) {
					viewSprite->at(i)->at(j)->ChangeTexture(1);
					Instance->SingUpToList(Layers::CollisionTile, viewSprite->at(i)->at(j));
				}
				posx += 2;
				viewSprite->at(i)->at(j)->SetPos(posx , posy, 0);
				cout << View[i, j];
			}	
		}
		posy -= 2;
		cout << endl;
	}
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
	if (scrollX >= 1) {
		LoadView();
		scrollX = 0;
		Instance->ClearLayer(Layers::BckTile);
		Instance->ClearLayer(Layers::CollisionTile);
	}
}