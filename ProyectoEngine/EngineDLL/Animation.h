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
	float timePerFrame;
	float currentTime;
	int currentFrame;
public:
	Animation(int columns, int rows);
	void SetAnimation(int initF, int finishF, float timePerF);
	float * UpdateAnimation(float deltaTime);
	~Animation();
};

