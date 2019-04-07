#include "Camera.h"




Camera::Camera(Renderer * _renderPrt)
{
	renderPtr = _renderPrt;

	camPos = glm::vec3(0, 0, 0);
	eyePos = glm::vec3(0, 0, 6);
	upPos = glm::vec3(0, 1, 0);

	roll = 0.0f;
	pitch = 0.0f;
	yaw = -90.0f;
	
	renderPtr->SetViewMatrix(camPos, eyePos, upPos);
	renderPtr->SetCameraType(CameraType::persp);
	renderPtr->SetProjectionMatrixPersp(-10.0f, 4.0f / 3.0f, 0.1f, 100.0f);
}

void Camera::Walk(float dir)
{
	camPos.z += dir;
	eyePos.z += dir;
	renderPtr->SetViewMatrix(camPos, eyePos, upPos);
}

void Camera::Starfe(float dir)
{
	camPos.x += dir;
	eyePos.x += dir;
	renderPtr->SetViewMatrix(camPos, eyePos, upPos);
}

void Camera::Translate(glm::vec3 direction)
{
	camPos += direction;
	eyePos += direction;
	renderPtr->SetViewMatrix(camPos, eyePos, upPos);
}

void Camera::Pitch(float degrees)
{
	renderPtr->CameraRotate(glm::vec3(0, degrees, 0));
}

void Camera::Yaw(float degrees)
{
	renderPtr->CameraRotate(glm::vec3(degrees, 0, 0));
}

void Camera::Roll(float degrees)
{
	renderPtr->CameraRotate(glm::vec3(0, 0, degrees));
}

Camera::~Camera()
{
}
