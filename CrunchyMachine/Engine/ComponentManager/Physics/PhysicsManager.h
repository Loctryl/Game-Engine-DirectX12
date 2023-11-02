#pragma once
#include <iostream>
#include <vector>
#include "Engine/ComponentManager/ComponentManager.h"
#include "Engine/Component/PhysicsComponent.h"

class CollisionGrid;
class GameObject;

class PhysicsManager : public ComponentManager<PhysicsComponent> {

public:
	PhysicsManager();
	~PhysicsManager();

	void CalculateNewPositions(float deltaTime);
	void ReCalculatePositions(PhysicsComponent* pc1, PhysicsComponent* pc2);
	void CheckCollision(float deltaTime);
	void Update(float deltaTime);

	void ClearCollisionGrid();
	void AddToCollisionGrid();

private:
	std::vector<CollisionGrid*> mCollisionGrid;
};