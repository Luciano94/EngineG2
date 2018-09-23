#pragma once
#include "Renderer.h"
#include "Exports.h"
class ENGINEDLL_API Entity
{
private:
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;
protected:
	Renderer * render;
	glm::mat4 WorldMatrix;
	glm::mat4 TranslateMatrix;
	glm::mat4 RotMatrix;
	glm::mat4 ScaleMatrix;
	void UpdateWorldMatrix();
public:
	virtual void Draw() = 0;
	Entity(Renderer * renderPTR);
	~Entity();
	void SetPos(float x, float y, float z);
	void SetRot(float x, float y, float z);
	void SetScale(float x, float y, float z);
	glm::vec3 GetPos();
	glm::vec3 GetRot();
	glm::vec3 GetScale();
};

