#pragma once
#include "Engine/GameObject.h"

class Camera;

// Asteroids manager, making them spawn
class AsteroCreator : public GameObject
{
	Camera* mCamera;
	XMFLOAT2 mSize;
	
	void OnInit() override;
	void OnUpdate(float deltaTime) override;
	void OnDestroy() override;
	void OnCollision(GameObject* go) override;

public:
	AsteroCreator();
	~AsteroCreator() override;
};