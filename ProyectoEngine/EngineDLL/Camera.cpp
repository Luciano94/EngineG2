#include "Camera.h"




Camera::Camera(Renderer * _renderPrt)
{
	renderPtr = _renderPrt;

	x = glm::vec4(1, 0, 0, 0);
	y = glm::vec4(0, 1, 0, 0);
	z = glm::vec4(0, 0, 1, 0);

	camPos = glm::vec4(0, 0, -50, 1);

	vMatrix = glm::lookAt(
		(glm::vec3)camPos,
		(glm::vec3)(camPos + z),
		(glm::vec3)y
	);


	renderPtr->SetCameraType(CameraType::persp);
	renderPtr->SetProjectionMatrixPersp(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 10000.0f);
	renderPtr->setVMatrix(vMatrix);
}

void Camera::Walk(float dir)
{
	camPos = glm::translate(glm::mat4(1.0f),(glm::vec3)(z * dir)) * camPos;
	vMatrix = glm::lookAt(
		(glm::vec3)camPos,
		(glm::vec3)(camPos + z),
		(glm::vec3)y
	);

	renderPtr->setVMatrix(vMatrix);
}

void Camera::Starfe(float dir)
{
	camPos = glm::translate(glm::mat4(1.0f), (glm::vec3)(x * dir)) * camPos;
	
	vMatrix = glm::lookAt(
		(glm::vec3)camPos,
		(glm::vec3)(camPos + z),
		(glm::vec3)y
	);

	renderPtr->setVMatrix(vMatrix);
}

void Camera::Translate(glm::vec3 direction)
{
	camPos = glm::translate(glm::mat4(1.0f), (glm::vec3)((x * direction.x) + (z * direction.z))) * camPos;

	vMatrix = glm::lookAt(
		(glm::vec3)camPos,
		(glm::vec3)(camPos + z),
		(glm::vec3)y
	);

	renderPtr->setVMatrix(vMatrix);
}

void Camera::Pitch(float degrees)
{
	z = glm::rotate(glm::mat4(1.0f), degrees, glm::vec3(1.0f, 0.0f, 0.0f)) * z;

	vMatrix = glm::lookAt(
		(glm::vec3)camPos,
		(glm::vec3)(camPos + z),
		(glm::vec3)y
	);

	renderPtr->setVMatrix(vMatrix);
}

void Camera::Yaw(float degrees)
{
	z = glm::rotate(glm::mat4(1.0f), degrees, glm::vec3(0.0f, 1.0f, 0.0f)) * z;
	x = glm::rotate(glm::mat4(1.0f), degrees, glm::vec3(0.0f, 1.0f, 0.0f)) * x;

	vMatrix = glm::lookAt(
		(glm::vec3)camPos,
		(glm::vec3)(camPos + z),
		(glm::vec3)y
	);

	renderPtr->setVMatrix(vMatrix);
}

void Camera::Roll(float degrees)
{
	x = glm::rotate(glm::mat4(1.0f), degrees, glm::vec3(0.0f, 0.0f, 1.0f)) * x;
	y = glm::rotate(glm::mat4(1.0f), degrees, glm::vec3(0.0f, 0.0f, 1.0f)) * y;

	vMatrix = glm::lookAt(
		(glm::vec3)camPos,
		(glm::vec3)(camPos + z),
		(glm::vec3)y
	);

	renderPtr->setVMatrix(vMatrix);
}

void Camera::Rotate(glm::vec3 rotation) {
	if (rotation.x != 0) {
		Yaw(rotation.x);
	}
	if(rotation.y != 0){
		Pitch(rotation.y);
	}
	if (rotation.z != 0) {
		Roll(rotation.z);
	}
}

Camera::~Camera()
{
}
