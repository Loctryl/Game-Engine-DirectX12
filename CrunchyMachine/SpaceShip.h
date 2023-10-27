#pragma once
#include "Engine/GameObject.h"


class SpaceShip : public GameObject
{
	void virtual OnInit(GameTimer* gt) override;
	void virtual OnUpdate(GameTimer* gt) override;
	void virtual OnDestroy(GameTimer* gt) override;

public:

	SpaceShip();
};

