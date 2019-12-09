#pragma once
#include <iostream>
#include "Exports.h"
#include "Renderer.h"
#include "Window.h"
#include "typeDef.h"
#include "Node.h"
#include "DeltaTime.h"
#include <GLFW/glfw3.h>

using namespace std;
class ENGINEDLL_API GameBase {
private:
	bool looping = false;
	bool hasScene = false;
	Node * SceneNode;
protected:
	Window * window;
	virtual bool OnStart() = 0;
	virtual bool OnStop() = 0;
	virtual bool OnUpdate() = 0;
	virtual void OnDraw() = 0;
	Renderer * render;
	DeltaTime * deltaTime;
public:
	bool Start(int h, int w, char* name);
	bool Stop();
	void Loop();
	void setScene(Node * _Scene);
	GameBase();
	~GameBase();
};

