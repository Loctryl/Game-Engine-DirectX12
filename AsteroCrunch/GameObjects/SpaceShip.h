#pragma once
#include "Engine/GameObject.h"

class Input;
class Camera;

class SpaceShip : public GameObject
{
	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;
	void virtual OnCollision(GameObject* gt) override;

	Input* mInput;
	Camera* mCam;


public:

	void SetCam(Camera* cam);
	SpaceShip();
};

