#include "BoundingDrawer.h"



BoundingDrawer::BoundingDrawer(Renderer * render) : Square(render)
{
}


BoundingDrawer::~BoundingDrawer()
{
}

void BoundingDrawer::DrawMesh(int typeDraw)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//render->LoadIMatrix();
	//render->SetWMatrix(WorldMatrix);

	if (material != NULL) {
		material->BindProgram();
		material->Bind("WVP");
		material->SetMatrixProperty(render->GetWVP());
	}

	render->BeginDraw(0);
	render->BindBuffer(0, bufferId, 3);
	render->BeginDraw(1);
	render->BindBuffer(1, colorBufferId, 3);
	render->DrawBuffer(vertexCount, typeDraw);
	render->EndDraw(0);
	render->EndDraw(1);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
