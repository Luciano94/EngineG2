#pragma once
#include <iostream>
#include "Exports.h"
#include "Renderer.h"
#include "Window.h"
#include "typeDef.h"
#include "Node.h"
#include <GLFW/glfw3.h>

using namespace std;
class ENGINEDLL_API GameBase {
private:
	double currentFrame;
	double lastFrame;
	bool looping = false;
	bool hasScene = false;
	Node * SceneNode;
protected:
	Window * window;
	Renderer * render;
	virtual bool OnStart() = 0;
	virtual bool OnStop() = 0;
	virtual bool OnUpdate() = 0;
	virtual void OnDraw() = 0;
	double deltaTime;
public:
	bool Start(int h, int w, char* name);
	bool Stop();
	void Loop();
	void getDeltaTime();
	void setScene(Node * _Scene);
	GameBase();
	~GameBase();
};

