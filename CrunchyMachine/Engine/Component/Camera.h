#pragma once
#include "Resources/framework.h"
#include "Engine/GameObject.h"

class Camera : public GameObject
{
	XMFLOAT3 mTarget = XMFLOAT3(0.0f, 0.0f, 0.0f);

	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;

public:
	Camera();

	XMFLOAT3 GetTarget();
	XMMATRIX GetView();

};

