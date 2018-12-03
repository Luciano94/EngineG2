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
	//ViewSprite
	for (int i = 0; i < viewW; i++){
		for (int j = 0; j < viewH; j++){
			delete viewSprite->at(i)->at(j);
		}
		delete viewSprite->at(i);
	}
	//Level
	for (int i = 0; i < lvlW; i++) {
		delete level->at(i);
	}
	delete level;
	//View
	for (int i = 0; i < viewW; i++){
		delete view->at(i);
	}
	delete view;
}

void TileMap::LoadView() {
	int posx;
	int posy = 9;
	lastposX = 0;
	lastposXR = viewH - 1;
	lastposY = 0;
	lastposYR = viewW - 1;
	for (int i = 0; i < viewW; i++) {
		posx = -12;
		for (int j = 0; j < viewH; j++) {
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
		posy -= 2;
	}
}



void TileMap::UpdateViewX() {
	int posx;
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
		viewSprite->at(j)->at(lastposX)->SetPos(posx + render->getCameraPos().x, posy, 0);
		posy -= 2;
	}
	if (lastposX < viewH-1) lastposX++;
	else lastposX = 0;
}

void TileMap::UpdateViewXReverse() {
	int posx;
	int posy = 9;

	//Update X
	for (int i = 0; i < viewW; i++) {
		for (int j = viewH-1; j <= 0; j--) {
			view->at(i)->at(j + 1) = view->at(i)->at(j);
		}
	}
	for (int i = 0; i < viewW; i++) {
		int pos = level->at(i)->at(Xlvl);
		view->at(i)->at(0) = pos;
	}
	//volver a dibujar
	posx =  -10;
	for (int j = 0; j < viewW; j++) {
		if (view->at(j)->at(0) == 0) {
			viewSprite->at(j)->at(lastposXR)->ChangeTexture(0);
			Instance->SingUpToList(Layers::BckTile, viewSprite->at(j)->at(lastposX));
		}
		if (view->at(j)->at(0) == 1) {
			viewSprite->at(j)->at(lastposXR)->ChangeTexture(1);
			Instance->SingUpToList(Layers::CollisionTile, viewSprite->at(j)->at(lastposX));
		}
		viewSprite->at(j)->at(lastposXR)->SetPos(posx + render->getCameraPos().x, posy, 0);
		posy -= 2;
	}
	if (lastposXR >= 0) lastposXR--;
	else lastposXR = viewH-1;
}

void TileMap::UpdateViewY() {
	int posx = 12;
	int posy = 4;
	//Update Y
	for (int i = viewW-1; i >= 1; i--) {
		for (int j = 0; j < viewH; j++) {
			view->at(i)->at(j) = view->at(i-1)->at(j);
		}
	}
	for (int i = viewH-1; i >= 1; i--) {
		int pos = level->at(Ylvl)->at(i);
		view->at(0)->at(i) = pos;
	}
	cout << "asdasd" << endl;
	for (int i = 0; i < viewW; i++) {
		for (int j = 0; j < viewH; j++) {
			cout << view->at(i)->at(j);
		}
		cout << endl;
	}
	//volver a dibujar
	posx = -12;
	for (int j = viewH-1; j>=1; j--) {
		if (view->at(lastposYR)->at(j) == 0) {
			viewSprite->at(lastposYR)->at(j)->ChangeTexture(0);
			Instance->SingUpToList(Layers::BckTile, viewSprite->at(lastposYR)->at(j));
		}
		if (view->at(lastposYR)->at(j) == 1) {
			viewSprite->at(lastposYR)->at(j)->ChangeTexture(1);
			Instance->SingUpToList(Layers::CollisionTile, viewSprite->at(lastposYR)->at(j));
		}
		posx += 2;
		viewSprite->at(lastposYR)->at(j)->SetPos(posx , posy + render->getCameraPos().y, 0);
		cout<<"X: " << posx<<"Y: "<< posy - CurrentCameraPos.y << endl;
	}
	if (lastposY < viewW - 1) lastposY++;
	else lastposY = 0;
	if (lastposYR >=0) lastposYR--;
	else lastposYR = viewW-1;
}

void TileMap::UpdateViewYReverse(){
	int posx = 12;
	int posy = 4;
	//Update Y
	for (int i = viewW - 1; i >= 1; i--) {
		for (int j = 0; j < viewH; j++) {
			view->at(i)->at(j) = view->at(i - 1)->at(j);
		}
	}
	for (int i = viewH - 1; i >= 1; i--) {
		int pos = level->at(Ylvl)->at(i);
		view->at(0)->at(i) = pos;
	}
	cout << "asdasd" << endl;
	for (int i = 0; i < viewW; i++) {
		for (int j = 0; j < viewH; j++) {
			cout << view->at(i)->at(j);
		}
		cout << endl;
	}
	//volver a dibujar
	posx = -12;
	for (int j = viewH - 1; j >= 1; j--) {
		if (view->at(lastposYR)->at(j) == 0) {
			viewSprite->at(lastposYR)->at(j)->ChangeTexture(0);
			Instance->SingUpToList(Layers::BckTile, viewSprite->at(lastposYR)->at(j));
		}
		if (view->at(lastposYR)->at(j) == 1) {
			viewSprite->at(lastposYR)->at(j)->ChangeTexture(1);
			Instance->SingUpToList(Layers::CollisionTile, viewSprite->at(lastposYR)->at(j));
		}
		posx += 2;
		viewSprite->at(lastposYR)->at(j)->SetPos(posx, posy + render->getCameraPos().y, 0);
		cout << "X: " << posx << "Y: " << posy - CurrentCameraPos.y << endl;
	}
	if (lastposY < viewW - 1) lastposY++;
	else lastposY = 0;
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
		UpdateViewXReverse();
		scrollX = 0;
	}
	//UpdateY
	/*scrollY += DeltaCameraPos.y;
	cout << scrollY << endl;
	if (scrollY >= 2) {
		if (Ylvl < 0)Ylvl--;
		//if (Ylvl > lvlW - 1)Ylvl++;
		UpdateViewY();
		scrollY = 0;
	}//else
/*	if (scrollY <= -2) {
		if (Ylvl < 0)Ylvl--;
		UpdateViewY();
		scrollY = 0;
	}*/
}