#pragma once
#include "EngineResources/framework.h"
#include "Engine/GameObject.h"

class Input;

class Camera : public GameObject
{
	XMFLOAT3 mTarget;
	Input* mInput;

	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;
	void virtual OnCollision(GameObject* gt) override;

public:
	Camera();

	XMFLOAT3 GetTarget();
	XMMATRIX GetView();

};

