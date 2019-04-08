#include "Camera.h"




Camera::Camera(Renderer * _renderPrt)
{
	renderPtr = _renderPrt;

	vMatrix = renderPtr->getVMatrix();
	renderPtr->SetCameraType(CameraType::persp);
	renderPtr->SetProjectionMatrixPersp(-10.0f, 4.0f / 3.0f, 0.1f, 100.0f);
}

void Camera::Walk(float dir)
{
	vMatrix = glm::translate(vMatrix, glm::vec3(0.0f, 0.0f, dir));
	renderPtr->setVMatrix(vMatrix);
}

void Camera::Starfe(float dir)
{
	vMatrix = glm::translate(vMatrix, glm::vec3(0.0f, dir, 0.0f));
	renderPtr->setVMatrix(vMatrix);
}

void Camera::Translate(glm::vec3 direction)
{
	vMatrix = glm::translate(vMatrix, direction);
	renderPtr->setVMatrix(vMatrix);
}

void Camera::Pitch(float degrees)
{
	vMatrix = glm::rotate(vMatrix, degrees, glm::vec3(0.0f, 1.0f, 0.0f));
	renderPtr->setVMatrix(vMatrix);
}

void Camera::Yaw(float degrees)
{
	vMatrix = glm::rotate(vMatrix, degrees, glm::vec3(-1.0f, 0.0f, 0.0f));
	renderPtr->setVMatrix(vMatrix);
}

void Camera::Roll(float degrees)
{
	vMatrix = glm::rotate(vMatrix, degrees, glm::vec3(0.0f, 0.0f, 1.0f));
	renderPtr->setVMatrix(vMatrix);
}

Camera::~Camera()
{
}
