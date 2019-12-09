#include "GameBase.h"

GameBase::GameBase() {
}

GameBase::~GameBase() {
}

bool GameBase::Start(int h, int w, char* name) {
	deltaTime = DeltaTime::GetInstance();
	cout << "GameBase::Start()" << endl;
	render = Renderer::GetInstance();
	window = new Window ();
	if(!window->Start(h,w,name))
		return false;
	if (!render->Start(window->getWin()))
		return false;	
	return OnStart();
}

void GameBase::Loop() {
	looping = true;
	render->setClearScreenColor(0.2f, 0.2f, 0.5f, 0.0f);
	while (looping && !window->ShouldClose()) {
		render->ClearScreen();	
		deltaTime->UpdateDeltaTime();
		looping = OnUpdate();
		if (SceneNode)
			SceneNode->Update();
		if (SceneNode)
			SceneNode->Draw();
		OnDraw();
		render->SwapBuffer();
		window->PollEvents();
	}
}

void GameBase::setScene(Node * _Scene)
{
	SceneNode = _Scene;
	hasScene = true;
	looping = false;
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
