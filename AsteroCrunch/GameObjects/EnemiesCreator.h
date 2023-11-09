#pragma once
#include "Engine/GameObject.h"
#define ENEMY_SPAWN_OFFSET 300.f;

class Camera;

class EnemiesCreator : public GameObject
{

	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;
	void virtual OnCollision(GameObject* gt) override;

	float mSize;
	Camera* mCamera;

	float mSpawnDelay = 10.0f;
	float mSpawnCooldown = 0.0f;

public:
	EnemiesCreator();
	~EnemiesCreator();
};