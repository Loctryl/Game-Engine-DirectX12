#pragma once
#include "Engine/GameObject.h"

class Astero : public GameObject
{
	void virtual OnInit(GameTimer* gt) override;
	void virtual OnUpdate(GameTimer* gt) override;
	void virtual OnDestroy(GameTimer* gt) override;

public:

	Astero();
};

