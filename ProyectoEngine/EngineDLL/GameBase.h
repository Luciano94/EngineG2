#pragma once
#include <iostream>
#include "Exports.h"
#include "Renderer.h"
#include "Window.h"
#include "typeDef.h"
using namespace std;
class ENGINEDLL_API GameBase {
private:
	Window * window;
protected:
	Renderer * render;
	virtual bool OnStart() = 0;
	virtual bool OnStop() = 0;
	virtual bool OnUpdate() = 0;
	virtual void OnDraw() = 0;
public:
	bool Start(int h, int w, char* name);
	bool Stop();
	void Loop();

	GameBase();
	~GameBase();
};

