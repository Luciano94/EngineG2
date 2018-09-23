#pragma once
#include<iostream>

using namespace std;
class Window {
private:
	void* window;
public:
	Window();
	~Window();
	bool Start(int h, int w, char* tittle);
	void* getWin() {return window;}
	bool Stop();
	bool ShouldClose();
	void PollEvents();
};

