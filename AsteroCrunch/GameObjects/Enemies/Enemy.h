#pragma once
#include "GameObjects/Entity.h"

class PhysicsComponent;
class SpaceShipPart;
class StateMachineComponent;

// Opponents in game, looking like X-WINGS from Star Wars
class Enemy : public Entity
{
	SpaceShipPart* mParts[5];
	PhysicsComponent* mPhysic;
	StateMachineComponent* mStateMachine;
	
	float mCurrentAcceleration = 30.0f;

	float mFireRate = 0.5f;
	float mFireCooldown = 0.0f;

	bool mIsFleeing = false;
	
	void OnInit() override;
	void OnUpdate(float deltaTime) override;
	void OnDestroy() override;
	void OnCollision(GameObject* go) override;

	void InitSpaceShipParts();

public:
	Enemy();
	~Enemy() override;
};