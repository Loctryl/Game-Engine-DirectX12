#pragma once
#include "GameObjects/Entity.h"
#include "Resources/framework.h"

class Input;
class Camera;
class Border;
class SpaceShipPart;
class Life;

// Player entity
class SpaceShip : public Entity
{
private:
	Input* mInput;
	Camera* mCam;
	PhysicsComponent* mPhysic;


	SpaceShipPart* mParts[4];
	Border* mBorders[4];
	Life* mLife;
	
	float mCurrentAcceleration = 20.0f;
	float mCurrentRotationSpeed = 40.0f;

	float mMaxSpeed = mCurrentAcceleration * ACCELERATION_TIME;
	float mMaxRotationSpeed = mCurrentRotationSpeed * ROTATION_ACCELERATION_TIME;

	float mMaxFovAlteration = ACCELERATION_TIME * FOV_MOUVEMENT_SCALING;
	float mFovAlteration = 0.0f;
	float mMinFovAlteration = 0.0f;

	float mFireRate = 3.0f;
	float mFireCooldown = 0.0f;
	
	void OnInit() override;
	void OnUpdate(float deltaTime) override;
	void OnDestroy() override;
	void OnCollision(GameObject* go) override;

	void InitSpaceShipParts();
	void InitBorders();
	void UpdateBorders() const;

	void HandleInput(float deltaTime);

public:
	SpaceShip();
	~SpaceShip() override;

	void SetCam(Camera* cam);

	inline void CreateLife(Life* life) { mLife = life; }
};

