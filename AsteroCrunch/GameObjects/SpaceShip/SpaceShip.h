#pragma once
#include "Entity.h"

class Input;
class Camera;
class SpaceShipPart;

class SpaceShip : public Entity
{
	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;
	void virtual OnCollision(GameObject* gt) override;

	void HandleInput(float deltaTime);

	Input* mInput;
	Camera* mCam;

	SpaceShipPart* mParts[6];
	PhysicsComponent* physic;

	float mCurrentAcceleration = 20.0f;
	float mCurrentRotationSpeed = 40.0f;

	float mMaxSpeed = 120.0f;
	float mMaxRotationSpeed = 70.0f;
public:
	void SetCam(Camera* cam);
	SpaceShip();
};

