#pragma once
#include "Exports.h"
#include "Window.h"
#include <iostream>
#include<glm/glm.hpp>
#include<glm\gtc\matrix_transform.hpp>

using namespace std;

class ENGINEDLL_API Renderer {
private:
	void* win;
	unsigned int VertexArrayID;
	glm::mat4 WorldMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;
public:
	bool Start(void* wnd);
	bool Stop();
	void setClearScreenColor(float r, float g, float b, float a);
	unsigned int GenBuffer(float* buffer, int size);
	void BeginDraw(unsigned int name);
	void EndDraw(unsigned int name);
	void BindDraw(unsigned int name);
	void DrawBuffer(unsigned int vtxBuffer, int size);
	void DestroyBuffer(unsigned int buffer);
	void ClearScreen();
	void SwapBuffer();

	Renderer();
	~Renderer();
};