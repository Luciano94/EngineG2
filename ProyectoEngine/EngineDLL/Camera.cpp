#include "Camera.h"
#include "Mesh.h"

void Camera::addBSP(Mesh * plane, glm::vec3 nodepos)
{
	if (!plane->getIsBsp())
		return;

	bspPlanes->push_back(generatePlane(nodepos, plane->getForwardBSP()));
	bspPlanesNormals->push_back(plane->getForwardBSP());
}

Camera::Camera(Renderer * _renderPrt): Component(render)
{
	type: ComponentsType::CameraComponent;
	renderPtr = _renderPrt;

	x = glm::vec4(1, 0, 0, 0);
	y = glm::vec4(0, 1, 0, 0);
	z = glm::vec4(0, 0, 1, 0);

	camPos = glm::vec4(0, 0, -50, 1);
	point = (camPos + z);
	up = y;
	vMatrix = glm::lookAt(
		(glm::vec3)camPos,
		(glm::vec3)point,
		(glm::vec3)up
	);

	nearD = 0.1f;
	farD = 1000.0f;
	ratio = 4.0f / 3.0f;
	angle = glm::radians(45.0f);

	renderPtr->SetCameraType(CameraType::persp);
	renderPtr->SetProjectionMatrixPersp(angle, ratio, nearD, farD);
	setCamInternals();
	setCamDef();
	renderPtr->setVMatrix(vMatrix);

	bspPlanes = new vector<glm::vec4>();
	bspPlanesNormals = new vector<glm::vec3>();
}



void Camera::Walk(float dir)
{
	camPos = glm::translate(glm::mat4(1.0f),(glm::vec3)(z * dir)) * camPos;
	vMatrix = glm::lookAt(
		(glm::vec3)camPos,
		(glm::vec3)(camPos + z),
		(glm::vec3)y
	);

	setCamDef();
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

	setCamDef();
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

	setCamDef();
	renderPtr->setVMatrix(vMatrix);
}

void Camera::Pitch(float degrees)
{
	z = glm::rotate(glm::mat4(1.0f), degrees, glm::vec3(x.x, x.y, x.z)) * z;
	y = glm::rotate(glm::mat4(1.0f), degrees, glm::vec3(x.x, x.y, x.z)) * y;

	vMatrix = glm::lookAt(
		(glm::vec3)camPos,
		(glm::vec3)(camPos + z),
		(glm::vec3)y
	);

	setCamDef();
	renderPtr->setVMatrix(vMatrix);
}

void Camera::Yaw(float degrees)
{
	z = glm::rotate(glm::mat4(1.0f), degrees, glm::vec3(y.x, y.y, y.z)) * z;
	x = glm::rotate(glm::mat4(1.0f), degrees, glm::vec3(y.x, y.y, y.z)) * x;

	vMatrix = glm::lookAt(
		(glm::vec3)camPos,
		(glm::vec3)(camPos + z),
		(glm::vec3)y
	);

	setCamDef();
	renderPtr->setVMatrix(vMatrix);
}

void Camera::Roll(float degrees)
{
	x = glm::rotate(glm::mat4(1.0f), degrees, glm::vec3(z.x, z.y, z.z)) * x;
	y = glm::rotate(glm::mat4(1.0f), degrees, glm::vec3(z.x, z.y, z.z)) * y;

	vMatrix = glm::lookAt(
		(glm::vec3)camPos,
		(glm::vec3)(camPos + z),
		(glm::vec3)y
	);

	setCamDef();
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

void Camera::setCamInternals()
{
	// compute width and height of the near and far plane sections
	tang = glm::tan(angle * 0.5f);
	nh = nearD * tang;
	nw = nh * ratio;
	fh = farD * tang;
	fw = fh * ratio;
}

void Camera::setCamDef()
{
	glm::vec3 right = (glm::vec3)x;
	glm::vec3 up = (glm::vec3)y;

	glm::vec3 nearCenter = (glm::vec3)camPos + (glm::vec3)z * nearD;
	glm::vec3 farCenter = (glm::vec3)camPos + (glm::vec3)z * farD;

	glm::vec3 leftPlaneVec = (nearCenter - right * nw) - (glm::vec3)camPos;
	glm::vec3 rightPlaneVec = (nearCenter + right * nw) - (glm::vec3)camPos;
	glm::vec3 topPlaneVec = (nearCenter + up * nh) - (glm::vec3)camPos;
	glm::vec3 bottomPlaneVec = (nearCenter - up * nh) - (glm::vec3)camPos;

	glm::vec3 normalLeft = glm::normalize(glm::cross(leftPlaneVec, up));
	glm::vec3 normalRight = -glm::normalize(glm::cross(rightPlaneVec, up));
	glm::vec3 normalTop = glm::normalize(glm::cross(topPlaneVec, right));
	glm::vec3 normalBottom = -glm::normalize(glm::cross(bottomPlaneVec, right));

	pl[NEARP] = generatePlane(-(glm::vec3)z, nearCenter);
	pl[FARP] = generatePlane((glm::vec3)z, farCenter);
	pl[LEFT] = generatePlane(normalLeft, (glm::vec3)camPos);
	pl[RIGHT] = generatePlane(normalRight, (glm::vec3)camPos);
	pl[TOP] = generatePlane(normalTop, (glm::vec3)camPos);
	pl[BOTTOM] = generatePlane(normalBottom, (glm::vec3)camPos);
}

glm::vec4 Camera::generatePlane(glm::vec3 normal, glm::vec3 point)
{
	glm::vec4 plane;

	plane.x = normal.x;
	plane.y = normal.y;
	plane.z = normal.z;
	plane.w = -glm::dot(normal, point);

	return plane;
}

int Camera::boxInFrustum(BoundingCube * boundingCube)
{
	bool isInsideFrustum = true;
	bool allOutsideCurrentPlane = false;

	for (int i = 0; i < (int)Planes::COUNT; i++)
	{
		allOutsideCurrentPlane = false;

		for (int j = 0; j < CUBE_VERTEX; j++)
		{
			glm::vec3 vertexPosition = boundingCube->getVertex(j);
			glm::vec3 planeNormal = glm::vec3(pl[i]);

			float dist = glm::dot(planeNormal, vertexPosition) + pl[i].w;
			if (dist < 0.0f)
				break;
			if (j == CUBE_VERTEX - 1)
				allOutsideCurrentPlane = true;
		}
		if (allOutsideCurrentPlane)
		{
			isInsideFrustum = false;
			break;
		}
	}
	if (isInsideFrustum)
		return States::INSIDE;
	else
		return States::OUTSIDE;
}

int Camera::boxInBSP(BoundingCube * boundingCube)
{
	bool inTheSamePosition = false;
	for (int i = 0; i < bspPlanes->size(); i++) {
		float cameraDistanceToPlane = getDistanceToPlane(camPos, bspPlanes->at(i), bspPlanesNormals->at(i));
		float cameraDistanceSign = glm::sign(cameraDistanceToPlane);
		for (int j = 0; j < CUBE_VERTEX; j++)
		{
			glm::vec3 vertexPosition = boundingCube->getVertex(j);
			float vertexDistanceToPlane = getDistanceToPlane(vertexPosition, bspPlanes->at(i), bspPlanesNormals->at(i));
			float vertexDistanceSign = glm::sign(vertexDistanceToPlane);

			if (vertexDistanceSign == cameraDistanceSign)
				break;
			if (j == CUBE_VERTEX - 1)
				inTheSamePosition = true;
		}
	}
	if (!inTheSamePosition)
		return States::INSIDE;
	else
		return States::OUTSIDE;
}

float Camera::getDistanceToPlane(glm::vec3 point, glm::vec4 _plane, glm::vec3 _planeNormal)
{
	float distance = 0.0f;

	distance = glm::dot(_planeNormal, point) + _plane.w;

	return distance;
}

Camera::~Camera()
{
}
