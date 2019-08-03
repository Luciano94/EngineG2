#include "Input.h"
#include "glm\glm.hpp"
#include "GL\glew.h"
#include "GLFW/glfw3.h"

using namespace glm;

Input * Input::instance = NULL;

void KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
}

Input::Input()
{
}

bool Input::isInput(int key)
{
	int state = glfwGetKey((GLFWwindow*)window->getWin(), key);
	if (state == GLFW_PRESS) return true;
	return false;
}

void Input::SetWindowContext(Window* window)
{
	this->window = window;
	glfwSetKeyCallback((GLFWwindow*)this->window->getWin(), KeyCallback);
}

void Input::PollEvents()
{
	glfwPollEvents();
}