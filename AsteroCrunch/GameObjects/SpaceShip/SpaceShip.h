#pragma once
#include "Engine/GameObject.h"

class Input;
class Camera;
class SpaceShipPart;

class SpaceShip : public GameObject
{
	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;
	void virtual OnCollision(GameObject* gt) override;

	void HandleInput(float deltaTime);

	Input* mInput;
	Camera* mCam;

	SpaceShipPart* mParts[3];

public:

	void SetCam(Camera* cam);
	SpaceShip();
};

