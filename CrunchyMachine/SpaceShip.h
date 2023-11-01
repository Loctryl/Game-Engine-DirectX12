#pragma once
#include "Engine/GameObject.h"


class SpaceShip : public GameObject
{
	void virtual OnInit(GameTimer* gt) override;
	void virtual OnUpdate(GameTimer* gt) override;
	void virtual OnDestroy(GameTimer* gt) override;
	void virtual OnCollision(GameObject* gt) override;

	PhysicsComponent* physics;

public:
	int mCountCollision;
	SpaceShip();
};

