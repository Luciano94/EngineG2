#include "Mesh.h"



Mesh::Mesh(Renderer * render) :Shape(render){
	shouldDispose = false;
	shouldDispouseColor = false;
	shouldDispouseIndices = false;

	bufferId = -1;
	colorBufferID = -1;
	indexBufferID = -1;

	vertexCount = 8;
	indexCount = 12;
	colorCount = 8;

	vertex = new float[vertexCount * 3]{
		// front
		-1.0, -1.0,  1.0,
		 1.0, -1.0,  1.0,
		 1.0,  1.0,  1.0,
		-1.0,  1.0,  1.0,
		// back
		-1.0, -1.0, -1.0,
		 1.0, -1.0, -1.0,
		 1.0,  1.0, -1.0,
		-1.0,  1.0, -1.0,
	};
	SetVertices(vertex, vertexCount);

	colorVertex = new float[colorCount * 3]{
		// front colors
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0,
		1.0, 1.0, 1.0,
		// back colors
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0,
		1.0, 1.0, 1.0,
	};
	SetColorVertex(colorVertex, colorCount);

	indices = new int[indexCount * 3]{
		// front
		0, 1, 2,
		2, 3, 0,
		// top
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// bottom
		4, 0, 3,
		3, 7, 4,
		// left
		4, 5, 1,
		1, 0, 4,
		// right
		3, 2, 6,
		6, 7, 3,
	};
	SetIndexVertex(indices, indexCount);

}

void Mesh::DisposeIndex() {
	if (shouldDispouseIndices) {
		render->DestroyBuffer(indexBufferID);
		shouldDispouseIndices = false;
	}
}

void Mesh::SetIndexVertex(int * indices, int count){
	DisposeIndex();

	indexCount = count;
	shouldDisposeColor = true;
	indexBufferID = render->GenMeshBuffer(indices, sizeof(int)* count * 3);
	render->BindMeshBuffer(indices,count,bufferId);
}

void Mesh::Draw(){
	DrawMesh(GL_TRIANGLES);
}


Mesh::~Mesh(){
	DisposeIndex();
}
