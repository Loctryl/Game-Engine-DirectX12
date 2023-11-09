#pragma once
#include "Engine/GameObject.h"

class SpaceShipPart : public GameObject
{
	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;
	void virtual OnCollision(GameObject* gt) override;


public:

	SpaceShipPart();
};