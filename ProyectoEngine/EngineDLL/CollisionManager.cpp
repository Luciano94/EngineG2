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
	for (int i = 0; i < (int)Layers::Count; i++) {
		groupsOfGOBox->at(i) = new list<Sprite*>();
	}
}

CollisionManager::~CollisionManager() {
	for (int i = 0; i < (int)Layers::Count; i++) {
		delete groupsOfGOBox->at(i);
	}
	delete groupsOfGOBox;;
}

/*BOX COLLISIONS*/
void CollisionManager::UpdatePhysicsBox(){
	for (int i = 0; i < (int)Layers::Count; i++){
		for (int j = 0; j < (int)Layers::Count; j++){
			if (j == Layers::BckTile || i == Layers::BckTile) continue;
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

	if (diffX <= (A->GetWidth()/2 + B->GetWidth()/2) &&
		diffY <= (A->GetHeigth()/2 + B->GetHeigth()/2)) {

		float penetrateX = (A->GetWidth() / 2 + B->GetWidth() / 2) - diffX;
		float penetrateY = (A->GetHeigth() / 2 + B->GetHeigth() / 2) - diffY;

		if (penetrateX > penetrateY) {
			VerticalCollision(SpriteA, SpriteB, A, B, penetrateY);
		}
		else {
			HorizontalCollision(SpriteA,SpriteB, A, B, penetrateX);
		}
	}
}

void CollisionManager::VerticalCollision(Sprite * SpriteA, Sprite * SpriteB, 
										BoundingBox * A, BoundingBox * B, float penetrateY) {
	if (A->isStatic()) { //A estatico
		SpriteB->SetPos(B->GetX(), B->GetY() - penetrateY, 0);
		B->SetCollision(true);
	}
	else if (B->isStatic()) { // B estatico
		SpriteA->SetPos(A->GetX(), A->GetY() - penetrateY, 0);
		A->SetCollision(true);
	}
	else {	//Default
		/*Calculo el porcentaje segun la masa de cada objeto*/
		float totalMass = A->GetMass() + B->GetMass();
		float AMassPercent = (A->GetMass() / totalMass) * 10;
		float BMassPercent = (B->GetMass() / totalMass) * 10;

		/*seteo su posicion*/
		SpriteA->SetPos(A->GetX(), A->GetY() + (penetrateY / AMassPercent), 0);
		SpriteB->SetPos(B->GetX(), B->GetY() - (penetrateY / BMassPercent), 0);
	}
}

void CollisionManager::HorizontalCollision(Sprite * SpriteA, Sprite * SpriteB,
							BoundingBox * A, BoundingBox * B, float penetrateX) {
	if (A->isStatic()) { //Si A es estatico
		SpriteB->SetPos(B->GetX() - penetrateX, B->GetY(), 0);
		B->SetCollision(true);
	}
	else if (B->isStatic()) { //Si B es estatico
		SpriteA->SetPos(A->GetX() - penetrateX, A->GetY(), 0);
		A->SetCollision(true);
	}
	else {	//Default
			/*Calculo el porcentaje segun la masa de cada objeto*/
		float totalMass = A->GetMass() + B->GetMass();
		float AMassPercent = (A->GetMass() / totalMass) * 10;
		float BMassPercent = (B->GetMass() / totalMass) * 10;

		SpriteA->SetPos(A->GetX() + (penetrateX / AMassPercent), A->GetY(), 0);
		SpriteB->SetPos(B->GetX() - (penetrateX / BMassPercent), B->GetY(), 0);
	}
}

void CollisionManager::ClearLayer(int Layer){
	groupsOfGOBox->at(Layer)->clear();
}

void CollisionManager::SingUpToList(Layers layer, Sprite * A){
	groupsOfGOBox->at(layer)->push_back(A);
}
