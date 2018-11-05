#include "CollisionManager.h"

CollisionManager::CollisionManager(){
	groupsOfGOBox = new vector<list<BoundingBox>*>((int)Layers::Count);
	groupsOfGOCircle = new vector<list<BoundingCircle>*>((int)Layers::Count);
	for (int i = 0; i < (int)Layers::Count; i++) {
		groupsOfGOBox->at(i) = new list<BoundingBox>();
		groupsOfGOCircle->at(i) = new list<BoundingCircle>();
	}
}

CollisionManager::~CollisionManager() {
	for (int i = 0; i < (int)Layers::Count; i++) {
		delete groupsOfGOBox->at(i);
		delete groupsOfGOCircle->at(i);
	}
	delete groupsOfGOBox;
	delete groupsOfGOCircle;
}

/*BOX COLLISIONS*/
void CollisionManager::UpdatePhysicsBox(){
	for (int i = 0; i < (int)Layers::Count; i++){
		for (int j = 0; j < (int)Layers::Count; j++){
			if (j == i) continue;
			LayersMatchBox(groupsOfGOBox->at(i), groupsOfGOBox->at(j));
		}
	}
}

void CollisionManager::LayersMatchBox(list<BoundingBox> * layerA, list<BoundingBox> * layerB){
	for (list<BoundingBox>::iterator i = layerA->begin(); i != layerA->end(); ++i) {
		for (list<BoundingBox>::iterator j = layerB->begin(); j != layerB->end(); ++j) {
			ResolveCollisionBox(*i , *j);
		}
	}
}

void CollisionManager::ResolveCollisionBox(BoundingBox A, BoundingBox B) {
	glm::vec2 dif = A.GetPos() - B.GetPos();
	unsigned int diffX = abs(dif.x);
	unsigned int diffY = abs(dif.y);

	if (diffX < (A.GetWigth()/2 + B.GetWigth()/2) && 
		diffY < (A.GetHeigth()/2 + B.GetHeigth()/2)) {
		unsigned int penetrateX = (A.GetWigth() / 2 + B.GetWigth() / 2) - diffX;
		unsigned int penetrateY = (A.GetHeigth() / 2 + B.GetHeigth() / 2) - diffY;

		if (penetrateX > penetrateY) {
			//VerticalCollision();
			if (A.isStatic())
				B.SetPos(B.GetX(), B.GetY() - penetrateY);
			else if(B.isStatic())
				A.SetPos(A.GetX(), A.GetY() - penetrateY);
			else {
				A.SetPos(A.GetX(), A.GetY() - (penetrateY/2));
				B.SetPos(B.GetX(), B.GetY() - (penetrateY/2));
			}
		}
		else {
			//HorizontalCollision();
			if (A.isStatic())
				B.SetPos(B.GetX()- penetrateX, B.GetY());
			else if (B.isStatic())
				A.SetPos(A.GetX() - penetrateX, A.GetY());
			else {
				A.SetPos(A.GetX() - (penetrateX / 2), A.GetY() );
				B.SetPos(B.GetX() - (penetrateY / 2), B.GetY());
			}
		}
	}
}

/*CIRCLE COLLISIONS*/
void CollisionManager::UpdatePhysicsCircle() {
	for (int i = 0; i < (int)Layers::Count; i++) {
		for (int j = 0; j < (int)Layers::Count; j++) {
			if (j == i) continue;
			LayersMatchCircle(groupsOfGOCircle->at(i), groupsOfGOCircle->at(j));
		}
	}
}

void CollisionManager::LayersMatchCircle(list<BoundingCircle>* layerA, list<BoundingCircle>* layerB){
	for (list<BoundingCircle>::iterator i = layerA->begin(); i != layerA->end(); ++i) {
		for (list<BoundingCircle>::iterator j = layerB->begin(); j != layerB->end(); ++j) {
			ResolveCollisionCircle(*i, *j);
		}
	}
}

void CollisionManager::ResolveCollisionCircle(BoundingCircle A, BoundingCircle B) {
}
