#pragma once
#include "Resources/framework.h"
#include "Engine/GameObject.h"
#include "Frustum.h"

class Camera : public GameObject
{
	XMFLOAT3 mTarget = XMFLOAT3(0.0f, 0.0f, 0.0f);
	RenderManager* mRenderManager;
	Frustum mFrustum;

	void virtual OnInit(GameTimer* gt) override;
	void virtual OnUpdate(GameTimer* gt) override;
	void virtual OnDestroy(GameTimer* gt) override;

public:
	Camera();

	XMFLOAT3 GetTarget();
	XMMATRIX GetView();
	Frustum GetFrustum();
};

