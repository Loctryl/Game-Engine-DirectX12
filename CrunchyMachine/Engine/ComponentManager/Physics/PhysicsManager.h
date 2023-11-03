#pragma once
#include <iostream>
#include <vector>
#include "Engine/ComponentManager/ComponentManager.h"
#include "Engine/Component/PhysicsComponent.h"

class CollisionGrid;
class GameObject;
class Transform;

class PhysicsManager : public ComponentManager<PhysicsComponent> {

public:
	PhysicsManager();
	~PhysicsManager();

	void CalculateNewPositions(float deltaTime);
	void ReCalculatePositions(PhysicsComponent* pc1, PhysicsComponent* pc2, float dist);
	void CheckCollision(float deltaTime);
	void Update(float deltaTime);

	Transform* GetRootTransform(PhysicsComponent* physicsComponent);

private:
	bool mIsIdependant; 
	std::vector<CollisionGrid*> mCollisionGrid;
};