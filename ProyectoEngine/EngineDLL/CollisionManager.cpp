#include "CollisionManager.h"

CollisionManager* CollisionManager::Instance = NULL;

CollisionManager * CollisionManager::GetInstance(){
	if (Instance == NULL) {
		Instance = new CollisionManager();
	}
	return Instance;
}

CollisionManager::CollisionManager(){
	groupsOfGOBox = new vector<list<Sprite*>*>((int)Layers::Count);
	groupsOfGOCircle = new vector<list<Sprite*>*>((int)Layers::Count);
	for (int i = 0; i < (int)Layers::Count; i++) {
		groupsOfGOBox->at(i) = new list<Sprite*>();
		groupsOfGOCircle->at(i) = new list<Sprite*>();
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

void CollisionManager::LayersMatchBox(list<Sprite*> * layerA, list<Sprite*> * layerB){
	for (list<Sprite*>::iterator i = layerA->begin(); i != layerA->end(); ++i) {
		for (list<Sprite*>::iterator j = layerB->begin(); j != layerB->end(); ++j) {
			ResolveCollisionBox(*i , *j);
		}
	}
}

void CollisionManager::ResolveCollisionBox(Sprite * SpriteA, Sprite * SpriteB) {
	BoundingBox * A = SpriteA->getBoundingBox();
	BoundingBox * B = SpriteB->getBoundingBox();
	glm::vec2 dif = A->GetPos() - B->GetPos();
	float diffX = abs(dif.x);
	float diffY = abs(dif.y);

	if (diffX <= (A->GetWigth()/2 + B->GetWigth()/2) &&
		diffY <= (A->GetHeigth()/2 + B->GetHeigth()/2)) {
		float penetrateX = (A->GetWigth() / 2 + B->GetWigth() / 2) - diffX;
		float penetrateY = (A->GetHeigth() / 2 + B->GetHeigth() / 2) - diffY;

		if (penetrateX > penetrateY) {
			//VerticalCollision();
			if (A->isStatic()) {
				SpriteB->SetPos(B->GetX(), B->GetY() - penetrateY, 0);
				B->SetCollision(true);
			}
			else if (B->isStatic()) {
				SpriteA->SetPos(A->GetX(), A->GetY() - penetrateY, 0);
				A->SetCollision(true);
			}
			else {

				SpriteA->SetPos(A->GetX(), A->GetY() + (penetrateY/2),0);
				SpriteB->SetPos(B->GetX(), B->GetY() - (penetrateY/2),0);
			}
		}
		else {
			//HorizontalCollision();
			if (A->isStatic()) {
				SpriteB->SetPos(B->GetX() - penetrateX, B->GetY(), 0);
				B->SetCollision(true);
			}
			else if (B->isStatic()) {
				SpriteA->SetPos(A->GetX() - penetrateX, A->GetY(), 0);
				A->SetCollision(true);
			}
			else {
				SpriteA->SetPos(A->GetX() + (penetrateX / 2), A->GetY() ,0);
				SpriteB->SetPos(B->GetX() - (penetrateX / 2), B->GetY(),0);
			}
		}
	}
}

void CollisionManager::SingUpToList(Layers layer, Sprite * A){
	groupsOfGOBox->at(layer)->push_back(A);
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

void CollisionManager::LayersMatchCircle(list<Sprite*> * layerA, list<Sprite*> * layerB){
	for (list<Sprite*>::iterator i = layerA->begin(); i != layerA->end(); ++i) {
		for (list<Sprite*>::iterator j = layerB->begin(); j != layerB->end(); ++j) {
			ResolveCollisionCircle(*i, *j);
		}
	}
}

void CollisionManager::ResolveCollisionCircle(Sprite  *A, Sprite *B) {
}
