#pragma once
#include "Engine/GameObject.h"
#define ENEMY_SPAWN_OFFSET 300.f;

class Camera;

// Enemies manager, making them spawn
class EnemiesCreator : public GameObject
{
	float mSize;
	Camera* mCamera;

	float mSpawnDelay = 10.0f;
	float mSpawnCooldown = 0.0f;
	
	void OnInit() override;
	void OnUpdate(float deltaTime) override;
	void OnDestroy() override;
	void OnCollision(GameObject* go) override;

public:
	EnemiesCreator();
	~EnemiesCreator() override;
};