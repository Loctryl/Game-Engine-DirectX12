#pragma once
#include "EngineResources/framework.h"
#include "Engine/GameObject.h"

class SkyBox : public GameObject
{
	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;
	void virtual OnCollision(GameObject* gt) override;

public:
	SkyBox();
};

