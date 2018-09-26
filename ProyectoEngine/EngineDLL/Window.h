#pragma once
#include<iostream>
#include "Exports.h"
using namespace std;
class ENGINEDLL_API Window {
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

