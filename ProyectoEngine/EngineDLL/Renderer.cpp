#include "Renderer.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
using namespace std;

bool Renderer::Start(void* wnd) {
	cout << "Renderer::Start()" << endl;
	win = wnd;
	glfwMakeContextCurrent((GLFWwindow*)wnd);
	if (glewInit() != GLEW_OK) {
		cout << "Falló al inicializar GLEW\n" << endl;
		return -1;
	}

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	ProjectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.f);
	
	camPos = glm::vec3(0, 0, 0);
	eyePos = glm::vec3(0, 0, 3);

	ViewMatrix = glm::lookAt(
		glm::vec3(0, 0, 3),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);

	WorldMatrix = glm::mat4(1.0f);

	UpdateWVP();

	return true;
}

bool Renderer::Stop() {
	cout << "Renderer::Stop()" << endl;
	return true;
}

void Renderer::setClearScreenColor(float r, float g, float b, float a){
	glClearColor(r, g, b, a);
}

unsigned int Renderer::GenBuffer(float * buffer, int size)
{
	unsigned int vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);
	return vertexBuffer;
}


void Renderer::BeginDraw(unsigned int atribID) {
	glEnableVertexAttribArray(atribID);
}

void Renderer::EndDraw(unsigned int atribID) {
	glDisableVertexAttribArray(atribID);
}

void Renderer::BindBuffer(unsigned int atribID, unsigned int vtxBuffer, unsigned int size) {
	glBindBuffer(GL_ARRAY_BUFFER, vtxBuffer);
	glVertexAttribPointer(
		atribID,            // debe corresponder en el shader.
		size,                  // tamaño
		GL_FLOAT,           // tipo
		GL_FALSE,           // normalizado?
		0,                  // Paso
		(void*)0            // desfase del buffer
	);
}

unsigned int Renderer::ChargeTexture(unsigned int width, unsigned int height, unsigned char * data)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);


	glBindTexture(GL_TEXTURE_2D, textureID);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glGenerateMipmap(GL_TEXTURE_2D);
	
	return textureID;
}

void Renderer::BindTexture(unsigned int texture, unsigned int textureID)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(textureID, 0);
}

void Renderer::DrawBuffer(int size, int typeDraw)
{
	glDrawArrays(typeDraw, 0, size);
}


void Renderer::UpdateMipMap(unsigned int textureID)
{
	glGenTextures(1, &textureID);


	glBindTexture(GL_TEXTURE_2D, textureID);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Renderer::DestroyBuffer(unsigned int buffer)
{
	glDeleteBuffers(1, &buffer);
}

void Renderer::ClearScreen(){
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::SwapBuffer(){
	glfwSwapBuffers((GLFWwindow*) win);
}

void Renderer::UpdateWVP()
{
	WVP = ProjectionMatrix * ViewMatrix * WorldMatrix;
}

glm::mat4 & Renderer::GetWVP()
{
	return WVP;
}

void Renderer::LoadIMatrix()
{
	WorldMatrix = glm::mat4(1.0f);
}

void Renderer::SetWMatrix(glm::mat4 matrix)
{
	WorldMatrix = matrix;
	UpdateWVP();
}

void Renderer::MultiplyWMatrix(glm::mat4 matrix)
{
	WorldMatrix *= matrix;
	UpdateWVP();
}

glm::vec3 Renderer::getCameraPos()
{
	return camPos;
}

void Renderer::CameraTranslate(glm::vec3 pos){
	
	camPos += pos;
	eyePos += glm::vec3(pos.x, pos.y, 0);

	ViewMatrix = glm::lookAt(
		eyePos,
		camPos,
		glm::vec3(0, 1, 0)
	);

	UpdateWVP();

}

Renderer::Renderer() {
}


Renderer::~Renderer() {
}
