#pragma once

#pragma once
#include "Entity.h"
#include "Resources/framework.h"

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


	float mCurrentAcceleration = 10.0f;

	float mMaxSpeed = mCurrentAcceleration * ACCELERATION_TIME;

	float mFireRate = 1.0f;
	float mFireCooldown = 0.0f;

public:
	Enemy();
};

