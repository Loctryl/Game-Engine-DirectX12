#pragma once
#include "Engine/GameObject.h"
#include "Engine/Component/ScriptComponent.h"

class Input;
class PhysicsComponent;
class DefaultState;

class Astero : public Script
{
	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;
	void virtual OnCollision(GameObject* gt) override;

public:

	Astero();

private:
	DefaultState* state;
	PhysicsComponent* physics;
};

