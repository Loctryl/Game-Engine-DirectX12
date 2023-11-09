#pragma once
#include "Engine/GameObject.h"

class PhysicsComponent;

// Elements that keep the player into a area
// Created in SpaceShip
class Border : public GameObject
{
	void OnInit() override;
	void OnUpdate(float deltaTime) override;
	void OnDestroy() override;
	void OnCollision(GameObject* go) override;

public:
	Border();
	~Border() override;

	PhysicsComponent* mPhysic;
};