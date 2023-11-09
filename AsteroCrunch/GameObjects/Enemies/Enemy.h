#pragma once
#include "GameObjects/Entity.h"

class PhysicsComponent;
class SpaceShipPart;
class StateMachineComponent;

class Enemy : public Entity
{
	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;
	void virtual OnCollision(GameObject* gt) override;

	void InitSpaceShipParts();

	SpaceShipPart* mParts[5];
	PhysicsComponent* physic;
	StateMachineComponent* mStateMachine;


	float mCurrentAcceleration = 30.0f;

	float mFireRate = 0.5f;
	float mFireCooldown = 0.0f;

	bool mIsFleeing = false;

public:
	Enemy();
};

