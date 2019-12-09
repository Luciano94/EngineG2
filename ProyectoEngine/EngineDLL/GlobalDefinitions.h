#pragma once
#include <vector>
#include<glm\glm.hpp>
#include<glm\gtc\matrix_transform.hpp>

#define GL_POINTS                         0x0000
#define GL_LINES                          0x0001
#define GL_LINE_LOOP                      0x0002
#define GL_LINE_STRIP                     0x0003
#define GL_TRIANGLES                      0x0004
#define GL_TRIANGLE_STRIP                 0x0005
#define GL_TRIANGLE_FAN                   0x0006
#define CUBE_VERTEX						  8

#define FULL_ROTATION					  360.0f

constexpr const float MAX_BYTE_VALUE = 255.0f;
constexpr const int CUBE_VERTICES = 8;
constexpr float DEFAULT_GRAVITY_Y = -9.81f;

enum Layers
{
	Player = 0,
	Enemy,
	EnemyBullet,
	PlayerBullet,
	CollisionTile,
	BckTile,
	Count
};

enum Directions
{
	Left=0,
	Rigth,
	Up,
	Down,
	Counts
};

enum CameraType {
	ortho = 0,
	persp,
	count
};

struct Header
{
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char * data;
};

struct MeshData {
	std::vector<float> * vertexArray;
	std::vector<float> * uvArray;
	std::vector<unsigned int> * indexArray;
};

enum ComponentsType{
	MeshRender = 0,
	CameraComponent,
	ColliderComponent,
	ScriptComponent,
	Transform,
	nullComponent
};

struct Vertex
{
	glm::vec3 m_pos;
	glm::vec2 m_tex;
	glm::vec3 m_normal;

	Vertex() {}

	Vertex(const glm::vec3& pos, const glm::vec2& tex, const glm::vec3& normal)
	{
		m_pos = pos;
		m_tex = tex;
		m_normal = normal;
	}
};

/*Camera*/

enum States { 
	OUTSIDE, 
	INTERSECT, 
	INSIDE 
};

/*Physix*/
enum class PrimitiveType
{
	LINES = 1,
	TRIANGLE = 4,
	TRIANGLE_STRIP = 5,
	TRIANGLE_FAN = 6,
	QUAD = 7
};

enum class ForceMode
{
	FORCE,
	IMPULSE,
	VELOCITY_CHANGE,
	ACCELERATION
};