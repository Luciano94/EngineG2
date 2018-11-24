#pragma once
#include "Shape.h"
#include "Material.h"
#include "Importer.h"
#include "Animation.h"
class ENGINEDLL_API Sprite : public Shape
{
private:

	Header texture;
	float * uvArray;
	unsigned int uvBufferID;
	unsigned int textureID;
	int uvVtxCount;
	bool shouldDispouseTexture;
	Animation * anim;

	bool onCollision;
public:
	void Draw() override;
	void DrawMeshWhitTexture(int typeDraw);
	void LoadMaterial(const char * bmpFile);
	void DispouseTexture();
	void SetTextureVertex(float * vertices, int count);
	
	void UpdAnim(float deltaTime);
	void SetAnim(int initF, int finishF, float timePerF);

	void setCollision();
	bool getCollision();

	Sprite(Renderer * render, int columns, int rows);
	~Sprite();
};

