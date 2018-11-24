#include "Animation.h"



Animation::Animation(int columns, int rows)
{
	sprSheet = new SpriteSheet(columns, rows, 1, 1);
	initFrame = 0;
	finishFrame = 0;
	timePerFrame = 0.1f;
	currentTime = 0.0f;
	currentFrame = 0;
}

void Animation::SetAnimation(int initF, int finishF, float timePerF)
{
	if (initF >= 0 && finishF < sprSheet->GetSize() && timePerF > 0) {
		initFrame = initF;
		finishFrame = finishF;
		timePerFrame = timePerF;
		currentTime = 0.0f;
		currentFrame = initFrame;
	}
}

float * Animation::UpdateAnimation(float deltaTime)
{
	cout << currentFrame << endl;
	currentTime += deltaTime;
	if (currentTime > timePerFrame) {
		currentTime = 0.0f;
		if (currentFrame < finishFrame)
			currentFrame++;
		else currentFrame = initFrame;
	}
	return sprSheet->GetSprite(currentFrame);
}


Animation::~Animation()
{
}
