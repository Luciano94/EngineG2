#pragma once

#define GL_POINTS                         0x0000
#define GL_LINES                          0x0001
#define GL_LINE_LOOP                      0x0002
#define GL_LINE_STRIP                     0x0003
#define GL_TRIANGLES                      0x0004
#define GL_TRIANGLE_STRIP                 0x0005
#define GL_TRIANGLE_FAN                   0x0006

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
