#pragma once
#include<list>
#include<vector>
#include"Sprite.h"
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
	vector<list<Sprite*>*> * groupsOfGOBox;
	void ResolveCollisionBox(Sprite * A, Sprite * B);

	void LayersMatchBox(list<Sprite*> * layerA, list<Sprite*> * layerB);

	/*Circle Collision*/
	vector<list<Sprite*>*> * groupsOfGOCircle;
	void ResolveCollisionCircle(Sprite * A, Sprite * B);
	void LayersMatchCircle(list<Sprite*> * layerA, list<Sprite*> * layerB);
	
	/*Singleton*/
	CollisionManager();
	static CollisionManager * Instance;
public:
	/*Singleton*/
	static CollisionManager * GetInstance();
	/*Box Collision*/
	void SingUpToList(Layers layer, Sprite * A);
	void UpdatePhysicsBox();
	/*Circle Collision*/
	void UpdatePhysicsCircle();

	~CollisionManager();
};
