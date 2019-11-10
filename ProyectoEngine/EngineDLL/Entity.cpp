#include "Entity.h"



Entity::Entity(Renderer * renderPTR){
	bBox = NULL;
	render = renderPTR;
	WorldMatrix = glm::mat4(1.0f);
	TranslateMatrix = glm::mat4(1.0f);
	RotMatrix = glm::mat4(1.0f);
	ScaleMatrix = glm::mat4(1.0f);

	pos[0] = pos[1] = pos[2] = 0.0f;
	rot[0] = rot[1] = rot[2] = 0.0f;
	scale[0] = scale[1] = scale[2] = 1.0f;
}



void Entity::SetRot(float x, float y, float z){
	rot[0] = x;
	rot[1] = y;
	rot[2] = z;

	RotMatrix = glm::rotate(glm::mat4(1.0f), x, glm::vec3(1.0f, 0.0f, 0.0f));
	RotMatrix *= glm::rotate(glm::mat4(1.0f), y, glm::vec3(0.0f, 1.0f, 0.0f));
	RotMatrix *= glm::rotate(glm::mat4(1.0f), z, glm::vec3(0.0f, 0.0f, 1.0f));

	UpdateWorldMatrix();
}

void Entity::SetScale(float x, float y, float z){
	scale[0] = x;
	scale[1] = y;
	scale[2] = z;

	ScaleMatrix = glm::scale(glm::mat4(1.0f), scale);

	UpdateWorldMatrix();
}

void Entity::Translate(float x, float y, float z){
	if (bBox == NULL) {
		pos[0] += x;
		pos[1] += y;
		pos[2] += z;
	}
	else if (!bBox->GetCollision()) {
		pos[0] += x;
		pos[1] += y;
		pos[2] += z;
		bBox->SetPos(pos[0], pos[1]);
		bBox->SetCollision(false);
	}
	TranslateMatrix = glm::translate(glm::mat4(1.0f), pos);
	UpdateWorldMatrix();
}

void Entity::Rotate(float x, float y, float z){
	rot[0] += x;
	rot[1] += y;
	rot[2] += z;

	RotMatrix = glm::rotate(glm::mat4(1.0f), rot[0], glm::vec3(1.0f, 0.0f, 0.0f));
	RotMatrix *= glm::rotate(glm::mat4(1.0f), rot[1], glm::vec3(0.0f, 1.0f, 0.0f));
	RotMatrix *= glm::rotate(glm::mat4(1.0f), rot[2], glm::vec3(0.0f, 0.0f, 1.0f));

	UpdateWorldMatrix();
}

void Entity::setRotationMatrix(float x, float y, float z, float w)
{
	float pitch, yaw, roll;

	glm::vec4 quaternion = glm::normalize(glm::vec4(x,y,z,w));

	convertToEulerAngles(quaternion, pitch, yaw, roll);

	rot = glm::vec3(pitch, yaw, roll);

	glm::mat4 mat1 = glm::mat4
	{
		quaternion.w, quaternion.z, -quaternion.y, quaternion.x,
		-quaternion.z, quaternion.w, quaternion.x, quaternion.y,
		quaternion.y, -quaternion.x, quaternion.w, quaternion.z,
		-quaternion.x, -quaternion.y, -quaternion.z, quaternion.w
	};

	glm::mat4 mat2 = glm::mat4
	{
		quaternion.w, quaternion.z, -quaternion.y, -quaternion.x,
		-quaternion.z, quaternion.w, quaternion.x, -quaternion.y,
		quaternion.y, -quaternion.x, quaternion.w, -quaternion.z,
		quaternion.x, quaternion.y, quaternion.z, quaternion.w
	};

	RotMatrix = mat1 * mat2;

	clampEulerRotation();
	UpdateWorldMatrix();
}

void Entity::convertToEulerAngles(const glm::vec4& quaternion, float& pitch, float& yaw, float& roll)
{
	float sinPitchCosYaw = 2.0f * (quaternion.w * quaternion.x + quaternion.y * quaternion.z);
	float cosPitchCosYaw = 1.0f - 2.0f * (quaternion.x * quaternion.x + quaternion.y * quaternion.y);
	pitch = glm::atan(sinPitchCosYaw, cosPitchCosYaw);

	float sinYaw = 2.0f * (quaternion.w * quaternion.y - quaternion.z * quaternion.x);
	yaw = (glm::abs(sinYaw) >= 1.0f) ? glm::sign(sinYaw) * glm::half_pi<float>() : glm::asin(sinYaw);

	float sinRollCosYaw = 2.0f * (quaternion.w * quaternion.z + quaternion.x * quaternion.y);
	float cosRollCosYaw = 1.0f - 2.0f * (quaternion.y * quaternion.y + quaternion.z * quaternion.z);
	roll = glm::atan(sinRollCosYaw, cosRollCosYaw);

	pitch = glm::degrees(pitch);
	yaw = glm::degrees(yaw);
	roll = glm::degrees(roll);
}

void Entity::clampEulerRotation()
{
	if (rot.x < 0.0f || rot.x >= FULL_ROTATION)
		rot.x = rot.x - (glm::floor(rot.x / FULL_ROTATION) * FULL_ROTATION);

	if (rot.y < 0.0f || rot.y >= FULL_ROTATION)
		rot.y = rot.y - (glm::floor(rot.y / FULL_ROTATION) * FULL_ROTATION);

	if (rot.z < 0.0f || rot.z >= FULL_ROTATION)
		rot.z = rot.z - (glm::floor(rot.z / FULL_ROTATION) * FULL_ROTATION);
}

void Entity::UpdateWorldMatrix(){
	WorldMatrix = TranslateMatrix * RotMatrix * ScaleMatrix;
}

glm::vec3 Entity::GetPos(){
	return pos;
}

glm::mat4 Entity::GetRotMatrix() {
	return RotMatrix;
}

glm::vec3 Entity::GetRot(){
	return rot;
}

glm::vec3 Entity::GetScale(){
	return scale;
}

Entity::~Entity(){
}

BoundingBox * Entity::getBoundingBox(){
	return bBox;
}

void Entity::SetPos(float x, float y, float z){
	if (bBox == NULL ) {
		pos[0] = x;
		pos[1] = y;
		pos[2] = z;
	}
	else if(!bBox->GetCollision()){
		pos[0] = x;
		pos[1] = y;
		pos[2] = z;
		bBox->SetPos(pos[0], pos[1]);
		bBox->SetCollision(false);
	}
		TranslateMatrix = glm::translate(glm::mat4(1.0f), pos);
		UpdateWorldMatrix();
}

void Entity::SetBoundingBox(float width, float heigth, bool isStatic, float bulk){
	bBox = new BoundingBox(glm::vec2(pos.x, pos.y), width, heigth, isStatic, bulk);
}

glm::mat4 Entity::GetWorldMatrix() {
	return WorldMatrix;
}