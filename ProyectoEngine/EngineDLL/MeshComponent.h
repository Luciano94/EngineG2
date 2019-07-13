#pragma once
#include "Component.h"
#include "
class MeshComponent : public Component
{
private: 
	unsigned int bufferId;
	unsigned int uvBufferID;
	unsigned int indexBufferID;
	unsigned int texID;

	float * vertex;
	float * uvVertex;
	unsigned int * indices;

	Material * material;
	unsigned int programID;

	unsigned int vertexCount;
	unsigned int uvCount;
	unsigned int indexCount;

	bool shouldDispose;
	bool shouldDispouseIndices;
	bool shouldDispouseTexture;
public:
	MeshComponent(Renderer * render);
	~MeshComponent();

	void Update();
	void Draw();
};

