#pragma once
#include "Exports.h"
#include "Window.h"
#include <iostream>

using namespace std;

class ENGINEDLL_API Renderer {
private:
	void* win;
	unsigned int VertexArrayID;
public:
	bool Start(void* wnd);
	bool Stop();
	void setClearScreenColor(float r, float g, float b, float a);
	unsigned int GenBuffer(float* buffer, int size);
	void DrawBuffer(unsigned int vtxBuffer, int size);
	void DestroyBuffer(unsigned int buffer);
	void ClearScreen();
	void SwapBuffer();

	Renderer();
	~Renderer();
};