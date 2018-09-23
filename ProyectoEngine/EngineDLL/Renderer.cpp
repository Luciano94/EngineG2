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

void Renderer::DrawBuffer(unsigned int vtxBuffer, int size)
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vtxBuffer);
	glVertexAttribPointer(
		0,                  // atributo 0. No hay razón particular para el 0, pero debe corresponder en el shader.
		3,                  // tamaño
		GL_FLOAT,           // tipo
		GL_FALSE,           // normalizado?
		0,                    // Paso
		(void*)0            // desfase del buffer
	);
	// Dibujar el triángulo !
	glDrawArrays(GL_TRIANGLES, 0, size); // Empezar desde el vértice 0S; 3 vértices en total -> 1 triángulo
	glDisableVertexAttribArray(0);
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

Renderer::Renderer() {
}


Renderer::~Renderer() {
}
