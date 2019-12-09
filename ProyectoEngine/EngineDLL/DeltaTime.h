#pragma once
#include "Exports.h"
#include <iostream>
#include <GLFW/glfw3.h>

using namespace std;

class ENGINEDLL_API DeltaTime
{
private:
	double currentFrame;
	double lastFrame;
	double deltaTime;

	/*Singleton*/
	DeltaTime();
	static DeltaTime * Instance;
public:
	/*Singleton*/
	static DeltaTime * GetInstance();
	~DeltaTime();

	/*Delta time*/
	void UpdateDeltaTime();
	double GetDeltaTime();

};

