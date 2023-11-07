#pragma once
#include "Engine/GameObject.h"

class PhysicsComponent;

class Astero : public GameObject
{
	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;
	void virtual OnCollision(GameObject* gt) override;

public:

	Astero(GameObject* parent ,float speed, XMFLOAT3 xOffset, XMFLOAT3 yOffset);

private:
	PhysicsComponent* physics;
	float mSpeed;
};

