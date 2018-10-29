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
	unsigned int ColorVertexArrayID;
	glm::mat4 WorldMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;
	glm::mat4 WVP;
public:
	bool Start(void* wnd);
	bool Stop();

	void setClearScreenColor(float r, float g, float b, float a);
	unsigned int GenBuffer(float* buffer, int size);

	void BeginDraw(unsigned int atribID);
	void EndDraw(unsigned int atribID);
	void BindBuffer(unsigned int atribID, unsigned int vtxBuffer, unsigned int size);
	unsigned int ChargeTexture(unsigned int width, unsigned int height, unsigned char * data);
	void BindTexture(unsigned int texture, unsigned int textureID);
	void DrawBuffer( int size, int typeDraw);

	void DestroyBuffer(unsigned int buffer);
	void ClearScreen();
	void SwapBuffer();

	void UpdateWVP();
	glm::mat4& GetWVP();
	void LoadIMatrix();
	void SetWMatrix(glm::mat4 matrix);
	void MultiplyWMatrix(glm::mat4 matrix);

	Renderer();
	~Renderer();
};