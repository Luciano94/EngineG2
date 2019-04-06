#pragma once
#include "Renderer.h"
#include "Exports.h"
#include "Window.h"
#include "GlobalDefinitions.h"
#include <glm/glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class ENGINEDLL_API Camera{
private:
	Renderer * renderPtr;
	CameraType camType;
	glm::mat4 perspMatrix;
	glm::mat4 orthoMatrix;
	glm::vec3 camPos;
	glm::vec3 eyePos;
	glm::vec3 upPos;

public:
	void Walk(float dir);
	void Starfe(float dir);
	void Translate(glm::vec3 direction);

	void Pitch(float degrees);
	void Yaw(float degrees);
	void Roll(float degrees);
	void Rotate(glm::vec4 rotation);

	Camera(Renderer * _renderPrt);
	~Camera();
};

