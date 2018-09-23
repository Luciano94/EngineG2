#include "GameBase.h"

GameBase::GameBase() {
}

GameBase::~GameBase() {
}
bool GameBase::Start(int h, int w, char* name) {
	cout << "GameBase::Start()" << endl;
	render = new Renderer();
	window = new Window ();
	if(!window->Start(h,w,name))
		return false;
	if (!render->Start(window->getWin()))
		return false;
	return OnStart();
}

void GameBase::Loop() {
	bool looping = true;
	render->setClearScreenColor(0.0f, 0.0f, 0.4f, 0.0f);
	while (looping && !window->ShouldClose()) {
		looping = OnUpdate();
		render->ClearScreen();
		OnDraw();
		render->SwapBuffer();
		window->PollEvents();
	}
}

bool GameBase::Stop() {
	cout << "GameBase::Stop()" << endl;
	if (!OnStop())
		cout << "Error deteniendo el juego"<<endl;
	if (!render->Stop())
		cout << "Error deteniendo render"<<endl;
	if (!window->Stop())
		cout << "Error deteniendo window" << endl;
	delete window;
	delete render;
	return true;
}
