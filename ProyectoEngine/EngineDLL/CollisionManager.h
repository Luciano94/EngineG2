#pragma once
#include<list>
#include<vector>
#include"Entity.h"
#include"BoundingBox.h"
#include"BoundingCircle.h"
#include"GlobalDefinitions.h"
#include<glm/glm.hpp>
#include<glm\gtc\matrix_transform.hpp>

using namespace std;

class ENGINEDLL_API CollisionManager
{
private:
	/*Box Collision*/
	vector<list<BoundingBox>*> * groupsOfGOBox;
	void ResolveCollisionBox(BoundingBox A, BoundingBox B);
	//void VerticalCollision(BoundingBox A, BoundingBox B);
	//void HorizontalCollision(BoundingBox A, BoundingBox B);

	/*Circle Collision*/
	vector<list<BoundingCircle>*> * groupsOfGOCircle;
	void ResolveCollisionCircle(BoundingCircle A, BoundingCircle B);
public:
	
	CollisionManager();
	void UpdatePhysicsBox();
	void LayersMatchBox(list<BoundingBox> * layerA, list<BoundingBox> * layerB);
	
	void UpdatePhysicsCircle();
	void LayersMatchCircle(list<BoundingCircle> * layerA, list<BoundingCircle> * layerB);

	~CollisionManager();
};
