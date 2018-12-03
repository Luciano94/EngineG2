#include "Tile.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>



Tile::Tile(Renderer * render, int columns, int rows) : Sprite(render, columns, rows){
	textures = new vector<int>();
}

void Tile::AddTexture(const char * bmpFile){
	Importer::LoadBMP(bmpFile, texture);
	textureID = render->ChargeTexture(texture.width, texture.height, texture.data);
	material->BindTexture("myTextureSampler");
	textures->push_back(textureID);
}

void Tile::ChangeTexture(int i){
	textureID = textures->at(i);
	render->UpdateTexture(textures->at(i));
	material->BindTexture("myTextureSampler");
}


Tile::~Tile(){
	delete textures;
}
