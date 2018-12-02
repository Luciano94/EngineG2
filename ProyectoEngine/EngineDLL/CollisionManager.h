#pragma once
#include<list>
#include<vector>
#include"Sprite.h"
#include"BoundingBox.h"
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

	void VerticalCollision(Sprite * SpriteA, Sprite * SpriteB, 
							BoundingBox * A, BoundingBox * B, float penetrateY);

	void HorizontalCollision(Sprite * SpriteA, Sprite * SpriteB, 
								BoundingBox * A, BoundingBox * B, float penetrateX);

	/*Singleton*/
	CollisionManager();
	static CollisionManager * Instance;
public:
	/*Singleton*/
	static CollisionManager * GetInstance();
	/*Box Collision*/
	void SingUpToList(Layers layer, Sprite * A);
	void UpdatePhysicsBox();
	/*Tile Collisions*/
	void ClearLayer(int Layer);

	~CollisionManager();
};
