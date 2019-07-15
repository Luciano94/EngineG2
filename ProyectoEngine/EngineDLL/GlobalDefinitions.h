#pragma once
#include <vector>
#include<glm/glm.hpp>
#include<glm\gtc\matrix_transform.hpp>

#define GL_POINTS                         0x0000
#define GL_LINES                          0x0001
#define GL_LINE_LOOP                      0x0002
#define GL_LINE_STRIP                     0x0003
#define GL_TRIANGLES                      0x0004
#define GL_TRIANGLE_STRIP                 0x0005
#define GL_TRIANGLE_FAN                   0x0006
#define CUBE_VERTEX						  8
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

/*Camera*/

enum States { 
	OUTSIDE, 
	INTERSECT, 
	INSIDE 
};