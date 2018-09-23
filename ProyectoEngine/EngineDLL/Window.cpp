#include "Window.h"
#include <GLFW/glfw3.h>

bool Window::Start(int h, int w, char* tittle) {
	cout << "Window::Start()"<<endl;
	if (!glfwInit()) {
		cout << "Error al iniciar GLFW" << endl;
	}
	window = glfwCreateWindow(h, w, tittle, NULL, NULL);
	if (!window) {
		glfwTerminate();
		return false;
	}
	return true;
}

bool Window::Stop() {
	if (window != NULL)
		glfwDestroyWindow((GLFWwindow*)window);
	window = NULL;
	glfwTerminate();
	cout <<"Window::Stop()"<<endl;
	return true;
}

bool Window::ShouldClose() {
	if (window)
		return glfwWindowShouldClose((GLFWwindow*)window);
	return true;
}

void Window::PollEvents() {
	glfwPollEvents();
}

Window::Window(){
}


Window::~Window(){
}
