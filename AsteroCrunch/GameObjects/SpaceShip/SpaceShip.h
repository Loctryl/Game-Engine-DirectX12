#pragma once
#include "Entity.h"
#include "Resources/framework.h"

class Input;
class Camera;
class Border;
class SpaceShipPart;

class SpaceShip : public Entity
{
	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;
	void virtual OnCollision(GameObject* gt) override;

	void InitSpaceShipParts();
	void InitBorders();
	void UpdateBorders();

	void HandleInput(float deltaTime);

	Input* mInput;
	Camera* mCam;

	SpaceShipPart* mParts[4];
	Border* mBorders[4];
	PhysicsComponent* physic;

	float mCurrentAcceleration = 20.0f;
	float mCurrentRotationSpeed = 40.0f;

	float mMaxSpeed = mCurrentAcceleration * ACCELERATION_TIME;
	float mMaxRotationSpeed = mCurrentRotationSpeed * ROTATION_ACCELERATION_TIME;

	float mMaxFOValteration = ACCELERATION_TIME * FOV_MOUVEMENT_SCALING;
	float mFOValteration = 0.0f;
	float mMinFOValteration = 0.0f;

public:
	void SetCam(Camera* cam);
	SpaceShip();
};

