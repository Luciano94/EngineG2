#include "Camera.h"




Camera::Camera(Renderer * _renderPrt)
{
	renderPtr = _renderPrt;

	camPos = glm::vec3(0, 0, 0);
	eyePos = glm::vec3(0, 0, 3);
	upPos = glm::vec3(0, 1, 0);
	
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
	upPos.x += degrees;
	renderPtr->SetViewMatrix(camPos, eyePos, upPos);
}

void Camera::Yaw(float degrees)
{
	eyePos.y += degrees;
	//upPos.y += degrees;
	renderPtr->SetViewMatrix(camPos, eyePos, upPos);
}

void Camera::Roll(float degrees)
{
	eyePos.x += degrees;
	renderPtr->SetViewMatrix(camPos, eyePos, upPos);
}

Camera::~Camera()
{
}
