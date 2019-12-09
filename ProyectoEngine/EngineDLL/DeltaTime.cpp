#include "DeltaTime.h"

DeltaTime * DeltaTime::Instance = NULL;

DeltaTime * DeltaTime::GetInstance() {
	if (Instance == NULL) {
		Instance = new DeltaTime();
	}
	return Instance;
}

DeltaTime::DeltaTime(){
	lastFrame = 0;
}


DeltaTime::~DeltaTime()
{
	delete Instance;
}

void DeltaTime::UpdateDeltaTime(){
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

double DeltaTime::GetDeltaTime(){
	return deltaTime;
}
