#pragma once
#include "EngineResources/framework.h"
#include "Engine/GameObject.h"
#define DEFAULT_FOV 80.0F


class Camera : public GameObject
{
	XMFLOAT3 mTarget = XMFLOAT3(0.0f, 0.0f, 0.0f);
	RenderManager* mRenderManager;
	//Frustum mFrustum;

	XMFLOAT4X4 mProjMatrix;
	XMFLOAT4X4 mViewProj;

	XMFLOAT4X4 mOrthoProjMatrix;
	XMFLOAT4X4 mOrthoViewProj;

	float mFovY = DEFAULT_FOV;
	float mNearZ = 0.05F;
	float mFarZ = 1000.0F;

	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;
	void virtual OnCollision(GameObject* gt) override;

	void CalculateProjMatrix();
	void CalculateOrthoProjMatrix();



public:


	Camera();

	float inline GetFov() { return mFovY; }
	void inline SetFOV(float fov) { mFovY = fov; CalculateProjMatrix(); }

	void SetTarget(XMFLOAT3 newTarget);
	XMFLOAT3 GetTarget();
	XMMATRIX GetView();
	XMMATRIX GetOrthoView();

	float GetFarZ() { return mFarZ; }
	XMFLOAT4X4 GetProj();
	XMFLOAT4X4 GetViewProj();
	XMFLOAT4X4 GetViewProjTranspose();

	XMFLOAT4X4 GetOrthoProj();
	XMFLOAT4X4 GetOrthoViewProj();
	XMFLOAT4X4 GetOrthoViewProjTranspose();
};

