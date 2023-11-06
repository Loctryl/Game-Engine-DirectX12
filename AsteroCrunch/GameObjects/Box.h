#pragma once
#include "Engine/Component/ScriptComponent.h"

class GameObject;

class Box : public Script
{
	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;
	void virtual OnCollision(GameObject* gt) override;

public:

	Box();
};
