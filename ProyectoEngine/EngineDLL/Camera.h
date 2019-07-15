#pragma once
#include "Renderer.h"
#include "Exports.h"
#include "Window.h"
#include "Component.h"
#include "BoundingCube.h"
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
	glm::vec4 up;
	glm::vec4 point;

	/*Frustum*/
	enum Planes{
		TOP = 0, BOTTOM, LEFT,
		RIGHT, NEARP, FARP, COUNT
	};

	glm::vec4 pl[COUNT];

	glm::vec3 ntl, ntr, nbl, nbr, ftl, ftr, fbl, fbr;

	float nearD, farD, ratio, angle, tang;
	float nw, nh, fw, fh;
public:
	void Walk(float dir);
	void Starfe(float dir);
	void Translate(glm::vec3 direction);

	void Pitch(float degrees);
	void Yaw(float degrees);
	void Roll(float degrees);
	void Rotate(glm::vec3 rotation);

	/*Frustum culling*/
	void setCamInternals();
	void setCamDef();
	glm::vec4 generatePlane(glm::vec3 normal, glm::vec3 point);
	int boxInFrustum(BoundingCube * BundingCube);

	Camera(Renderer * _renderPrt);
	~Camera();
};

