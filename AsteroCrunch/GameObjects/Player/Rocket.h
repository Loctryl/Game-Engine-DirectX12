#pragma once
#include "Engine/GameObject.h"

// Projectiles send by the player and the enemies
class Rocket : public GameObject
{
private:
	PhysicsComponent* mPhysic;
	float mSpeed;
	
	void OnInit() override;
	void OnUpdate(float deltaTime) override;
	void OnDestroy() override;
	void OnCollision(GameObject* go) override;
	
public:
	Rocket(float bulletSpeed = 700);
	~Rocket() override;
};