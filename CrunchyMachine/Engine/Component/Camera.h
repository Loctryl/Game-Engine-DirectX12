#pragma once
#include "EngineResources/framework.h"
#include "Engine/GameObject.h"

#define DEFAULT_FOV 80.0F

// Main and unique camera, providing all information for render pipeline
class Camera : public GameObject
{
private:
	XMFLOAT3 mTarget = XMFLOAT3(0.0f, 0.0f, 0.0f);
	RenderManager* mRenderManager;

	XMFLOAT4X4 mProjMatrix;
	XMFLOAT4X4 mViewProj;

	XMFLOAT4X4 mOrthoProjMatrix;
	XMFLOAT4X4 mOrthoViewProj;

	float mFovY = DEFAULT_FOV;
	float mNearZ = 0.05F;
	float mFarZ = 10000.0F;

	virtual void OnInit() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDestroy() override;
	virtual void OnCollision(GameObject* go) override;

	void CalculateProjMatrix();
	void CalculateOrthoProjMatrix();

public:
	Camera();
	~Camera() override;

	inline float GetFov() const { return mFovY; }
	inline void SetFov(float fov) { mFovY = fov; CalculateProjMatrix(); }

	inline XMFLOAT3 GetTarget() { return mTarget; }
	inline void SetTarget(XMFLOAT3 newTarget) { mTarget = newTarget; }

	inline float GetFarZ() const { return mFarZ; }
	
	inline XMFLOAT4X4 GetProj() const { return mProjMatrix; }
	XMMATRIX GetView() const;
	XMFLOAT4X4 GetViewProj() const;
	XMFLOAT4X4 GetViewProjTranspose() const;

	inline XMFLOAT4X4 GetOrthoProj() const { return mOrthoProjMatrix; }
	XMMATRIX GetOrthoView() const;
	XMFLOAT4X4 GetOrthoViewProj() const;
	XMFLOAT4X4 GetOrthoViewProjTranspose() const;
};