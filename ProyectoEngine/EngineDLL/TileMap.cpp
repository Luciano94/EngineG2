#include "Tilemap.h"

Tilemap::Tilemap(Renderer* _renderer, float _tilemapWidth, float _tilemapHeight, const char* _filename, 
				float _cantTilesX, float _cantTilesY, float _tileOffset, float _tileSize, 
				vector<int>* _colliderTiles) : Sprite(_renderer) {

	filename = _filename;
	tilemapWidth = _tilemapWidth;
	tilemapHeight = _tilemapHeight;
	cantTilesX = _cantTilesX;
	cantTilesY = _cantTilesY;
	tileOffset = _tileOffset;
	tileSize = _tileSize;
	vertexCount = _tilemapWidth * _tilemapHeight * 4 * 3;
	cantUVvertex = _tilemapWidth * _tilemapHeight * 4 * 2;


	mapIds = new vector<int>();
	LoadMapIDs(_filename);
	tilesWithCollides = new vector<int>();
	tilesWithCollides = _colliderTiles;
	tilesColliderData = new vector<TileColliderData>();
	int aux = 0;
	for (int i = 0; i < _tilemapHeight; i++) {
		for (int j = 0; j < _tilemapWidth; j++) {

			int col = j * 2;
			int row = i * 2;

			vertexArrayPos.push_back(-tileOffset + col);
			vertexArrayPos.push_back(tileOffset - row);
			vertexArrayPos.push_back(0.0f);

			vertexArrayPos.push_back(-tileOffset + col);
			vertexArrayPos.push_back((tileOffset - tileSize) - row);
			vertexArrayPos.push_back(0.0f);

			vertexArrayPos.push_back(-(tileOffset - tileSize) + col);
			vertexArrayPos.push_back((tileOffset - tileSize) - row);
			vertexArrayPos.push_back(0.0f);

			vertexArrayPos.push_back(-(tileOffset - tileSize) + col);
			vertexArrayPos.push_back(tileOffset - row);
			vertexArrayPos.push_back(0.0f);

			for (int k = 0; k < tilesWithCollides->size(); k++) {
				if (mapIds->at(aux) == tilesWithCollides->at(k)) {
					TileColliderData colliderAux;

					colliderAux.positionY = (tileOffset - row) - tileSize;
					colliderAux.positionX = (-tileOffset + col);
					colliderAux.layer = k;
					//cout << colliderAux.positionX << " - " << colliderAux.positionY << endl;
					colliderAux.height = tileSize;
					colliderAux.width = tileSize;
					tilesColliderData->push_back(colliderAux);
				}
			}

			aux++;

		}
	}
	float* p = &vertexArrayPos[0];

	uvArray = new float[cantUVvertex];
	LoadUVs();

	SetTilemapVertex(p, vertexCount);

	SetTextures(uvArray, cantUVvertex);
}

Tilemap::~Tilemap() {

}

void Tilemap::SetTextures(float* vertex, int cant) {

	uvBufferID = render->GenBuffer(vertex, sizeof(float)* cant);
}

void Tilemap::LoadTexture(const char* name) {
	Importer::LoadBMP(name, texture);
	textureID = render->ChargeTexture(texture.width, texture.height, texture.data);
	material->BindTexture("myTextureSampler");
}

void Tilemap::DrawMesh(int typeDraw) {
	render->LoadIMatrix();
	render->SetWMatrix(WorldMatrix);

	if (material != NULL) {
		material->BindProgram();
		material->Bind("WVP");
		material->SetMatrixProperty(render->GetWVP());
	}

	render->BindTexture(textureID, uvBufferID);
	render->BeginDraw(0);
	render->BindBuffer(0, bufferId, 3);
	render->BeginDraw(1);
	render->BindBuffer(1, uvBufferID, 2);
	render->DrawBuffer(vertexCount, typeDraw);
	render->EndDraw(0);
	render->EndDraw(1);
}

void Tilemap::Draw() {
	DrawMesh(PRIMITIVE_QUAD);
}

void Tilemap::LoadMapIDs(const char* _file) {
	string buffer;
	ifstream tileFile(_file);

	while (getline(tileFile, buffer, ',')) {
		mapIds->push_back(stoi(buffer));
	}
}

void Tilemap::LoadUVs() {
	float textureW = 1 / cantTilesX;
	float textureH = 1 / cantTilesY;

	int idIndex = 0;

	for (int i = 0; i < cantUVvertex; i = i + 8) {
		uvArray[i] = 0.0f;
		uvArray[i + 1] = 1.0f;

		uvArray[i + 2] = 0.0f;
		uvArray[i + 3] = 1.0f - textureH;

		uvArray[i + 4] = textureW;
		uvArray[i + 5] = 1.0f - textureH;

		uvArray[i + 6] = textureW;
		uvArray[i + 7] = 1.0f;

		int row = 0;
		int column = mapIds->at(idIndex);

		while (column >= cantTilesX) {
			column -= cantTilesX;
			row++;
		}

		uvArray[i] += textureW * column;
		uvArray[i + 1] -= textureH * row;

		uvArray[i + 2] += textureW * column;
		uvArray[i + 3] -= textureH * row;

		uvArray[i + 4] += textureW * column;
		uvArray[i + 5] -= textureH * row;

		uvArray[i + 6] += textureW * column;
		uvArray[i + 7] -= textureH * row;

		idIndex++;
	}
}

void Tilemap::SetTilemapVertex(float* _vertex, int _cant) {
	bufferId = render->GenBuffer(_vertex, sizeof(float) * _cant);
}


int Tilemap::NextTileIsCollider(float _playerTranslationX, float _playerTranslationY, float _playerHeight, float _playerWidht) {

	float col = (((_playerTranslationX - GetPos().x) / tileSize) * tileSize) + GetPos().x;
	float row = (((_playerTranslationY + GetPos().y) / tileSize) * tileSize) - GetPos().y;

	for (int i = 0; i < tilesColliderData->size(); i++) {
		if (((col + (_playerWidht / 2)) >= tilesColliderData->at(i).positionX) && ((col - (_playerWidht / 2)) <= tilesColliderData->at(i).positionX + tilesColliderData->at(i).width) && (row + (_playerHeight / 2) >= tilesColliderData->at(i).positionY) && (row - (_playerHeight / 2) <= tilesColliderData->at(i).positionY + tilesColliderData->at(i).height)) {
			return tilesColliderData->at(i).layer;
		}
	}
	return -1;
}

void Tilemap::UpdateTilemapColliderPosition(float _diferenceX, float _diferenceY) {
	for (int i = 0; i < tilesColliderData->size(); i++) {
		tilesColliderData->at(i).positionX += _diferenceX;
		tilesColliderData->at(i).positionY += _diferenceY;
	}
}