#pragma once
#include "SpriteSheet.h"
#include "Exports.h"
#include <iostream>

using namespace std;

class ENGINEDLL_API Animation
{
private:

	SpriteSheet * sprSheet;

	int initFrame;
	int finishFrame;
	int currentFrame;
	
	float timePerFrame;
	float currentTime;
	

public:

	Animation(int columns, int rows);
	void SetAnimation(int initF, int finishF, float timePerF);
	float * UpdateAnimation(float deltaTime);

	int getCurrentFrame();
	
	~Animation();
};

