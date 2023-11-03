#pragma once
#include "EngineResources/framework.h"
#include "Engine/GameObject.h"


class Camera : public GameObject
{
	XMFLOAT3 mTarget;

	XMFLOAT4X4 mProjMatrix;
	XMFLOAT4X4 mViewProj;

	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;

	void CalculateProjMatrix();

public:
	Camera();

	XMFLOAT3 GetTarget();
	XMMATRIX GetView();

	XMFLOAT4X4 GetProj();
	XMFLOAT4X4 GetViewProj();
};

