#pragma once
#include "Engine/GameObject.h"

class Camera;

class AsteroCreator : public GameObject
{

	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;
	void virtual OnCollision(GameObject* gt) override;
	Camera* mCamera;

	XMFLOAT2 mSize;
public:
	AsteroCreator();
};


