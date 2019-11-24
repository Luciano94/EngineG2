#include "Square.h"
#include "Renderer.h"
#include "Exports.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>

class ENGINEDLL_API BoundingDrawer: public Square
{
public:
	BoundingDrawer(Renderer * render);
	~BoundingDrawer();
	void DrawMesh(int typeDraw);
};

