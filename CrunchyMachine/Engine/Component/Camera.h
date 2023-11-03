#pragma once
#include "EngineResources/framework.h"
#include "Engine/GameObject.h"
#include "Frustum.h"

class Input;

class Camera : public GameObject
{
	XMFLOAT3 mTarget = XMFLOAT3(0.0f, 0.0f, 0.0f);
	RenderManager* mRenderManager;
	Frustum mFrustum;

	Input* mInput;

	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;
	void virtual OnCollision(GameObject* gt) override;

	Frustum CalcFrustum(float aspect, float fovY, float zNear, float zFar);

public:
	Camera();

	XMFLOAT3 GetTarget();
	XMMATRIX GetView();
	Frustum* GetFrustum();
};