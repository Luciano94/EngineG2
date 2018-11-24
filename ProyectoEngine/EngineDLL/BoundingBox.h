#pragma once
#include "Exports.h"
#include "GlobalDefinitions.h"
#include<glm/glm.hpp>
#include<glm\gtc\matrix_transform.hpp>

class ENGINEDLL_API BoundingBox{
private:
	bool staticBox;		//si el objeto es estatico
	bool isCollision;	// si el objeto colisiono o no	

	float mass;		//masa
	float width;	//ancho
	float heigth;	//alto
	glm::vec2 pos;	//posicion
public:
	BoundingBox(glm::vec2 pos, unsigned int width, unsigned int heigth, bool setStatic, float bulk);
	~BoundingBox();

	bool isStatic();

	float GetX();
	float GetY();

	glm::vec2 GetPos();
	void SetPos(float x, float y);

	float GetWidth();
	float GetHeigth();
	float GetMass();

	bool GetCollision();
	void SetCollision(bool value);
};

