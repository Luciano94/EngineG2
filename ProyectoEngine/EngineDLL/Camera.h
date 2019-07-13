#pragma once
#include "Renderer.h"
#include "Exports.h"
#include "Window.h"
#include "Component.h"
#include "GlobalDefinitions.h"
#include <glm/glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class ENGINEDLL_API Camera: public Component{
private:
	Renderer * renderPtr;
	CameraType camType;

	glm::mat4 vMatrix;

	glm::vec4 x;
	glm::vec4 y;
	glm::vec4 z;

	glm::vec4 camPos;

public:
	void Walk(float dir);
	void Starfe(float dir);
	void Translate(glm::vec3 direction);

	void Pitch(float degrees);
	void Yaw(float degrees);
	void Roll(float degrees);
	void Rotate(glm::vec3 rotation);

	Camera(Renderer * _renderPrt);
	~Camera();
};

