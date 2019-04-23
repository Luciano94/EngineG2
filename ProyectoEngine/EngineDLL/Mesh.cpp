#include "Mesh.h"



Mesh::Mesh(Renderer * render) :Entity(render){
	shouldDispose = false;
	bufferId = -1;
	vertexCount = -1;

	vertex = new float[32]{
	  0.0, 0.0, 0.0,
	  0.0, 0.0, 1.0,
	  0.0, 1.0, 0.0,
	  0.0, 1.0, 1.0,
	  1.0, 0.0, 0.0,
	  1.0, 0.0, 1.0,
	  1.0, 1.0, 0.0,
	  1.0, 1.0, 1.0
	};

	vertexCount = 8;
	shouldDispose = true;
	bufferId = render->GenBuffer(vertex, sizeof(float)* vertexCount * 3);
}


Mesh::~Mesh()
{
}
