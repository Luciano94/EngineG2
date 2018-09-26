#include "Renderer.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
using namespace std;

bool Renderer::Start(void* wnd) {
	cout << "Renderer::Start()" << endl;
	win = wnd;
	glfwMakeContextCurrent((GLFWwindow*)wnd);
	
	if (glewInit() != GLEW_OK) {
		cout << "Fall� al inicializar GLEW\n" << endl;
		return -1;
	}
	
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	ProjectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.f);

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
	// Dibujar el tri�ngulo !
	glDisableVertexAttribArray(atribID);
}

void Renderer::BindDraw(unsigned int atribID) {
	glVertexAttribPointer(
		atribID,                  // atributo 0. No hay raz�n particular para el 0, pero debe corresponder en el shader.
		3,                  // tama�o
		GL_FLOAT,           // tipo
		GL_FALSE,           // normalizado?
		0,                    // Paso
		(void*)0            // desfase del buffer
	);
}

void Renderer::DrawBuffer(unsigned int vtxBuffer, int size)
{
	glBindBuffer(GL_ARRAY_BUFFER, vtxBuffer);
	
	glDrawArrays(GL_TRIANGLES, 0, size); // Empezar desde el v�rtice 0S; 3 v�rtices en total -> 1 tri�ngulo
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

Renderer::Renderer() {
}


Renderer::~Renderer() {
}
