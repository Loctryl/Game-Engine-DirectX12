#pragma once
#include <iostream>
#include <vector>
#include "Engine/ComponentManager/ComponentManager.h"
#include "Engine/Component/PhysicsComponent.h"


class GameObject;

class PhysicsManager : public ComponentManager<PhysicsComponent> {

public:
	PhysicsManager();
	~PhysicsManager();

	void CalculateNewPositions(float deltaTime);
	void CheckCollision(float deltaTime);
	void Update(float deltaTime);

private:

};