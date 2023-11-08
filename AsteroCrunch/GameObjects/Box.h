#pragma once
#include "Engine/GameObject.h"

class SpaceShipPart;

class Box : public GameObject
{
	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;
	void virtual OnCollision(GameObject* gt) override;

	SpaceShipPart* mParts[5];
public:

	Box();
};
