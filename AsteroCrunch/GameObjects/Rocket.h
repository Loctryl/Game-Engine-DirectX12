#include "Engine/GameObject.h"
#pragma once
class Rocket : public GameObject
{
	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;
	void virtual OnCollision(GameObject* gt) override;

	PhysicsComponent* physic;

	float mSpeed;

public:

	Rocket(float mBulletSpeed = 700);
	~Rocket();
};

