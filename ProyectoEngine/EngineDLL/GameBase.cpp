#include "GameBase.h"

GameBase::GameBase() {
}

GameBase::~GameBase() {
}

bool GameBase::Start(int h, int w, char* name) {
	lastFrame = 0;
	cout << "GameBase::Start()" << endl;
	render = new Renderer();
	window = new Window ();
	if(!window->Start(h,w,name))
		return false;
	if (!render->Start(window->getWin()))
		return false;
	camera = new Camera(render);
	return OnStart();
}

void GameBase::Loop() {
	bool looping = true;
	render->setClearScreenColor(0.2f, 0.2f, 0.5f, 0.0f);
	while (looping && !window->ShouldClose()) {
		getDeltaTime();
		camera->Pitch(1 * deltaTime);
		looping = OnUpdate();
		render->ClearScreen();
		OnDraw();
		render->SwapBuffer();
		window->PollEvents();
	}
}

void GameBase::getDeltaTime(){
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
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
