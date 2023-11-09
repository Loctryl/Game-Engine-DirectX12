#pragma once
#include "Engine/ComponentManager/ComponentManager.h"
#include "Engine/Component/PhysicsComponent.h"

class GameObject;
class Transform;

// Physic engine that manages collisions, rigidbody and velocity
class PhysicsManager : public ComponentManager<PhysicsComponent> {
private:
	bool mIsIndependent = false; 
	
public:
	PhysicsManager();
	~PhysicsManager() override = default;
	
	void Update(float deltaTime) override;

	void CalculateNewPositions(float deltaTime) const;
	void ReCalculatePositions(PhysicsComponent* pc1, PhysicsComponent* pc2, float dist);
	void CheckCollision(float deltaTime);

	Transform* GetRootTransform(PhysicsComponent* physicsComponent);
};