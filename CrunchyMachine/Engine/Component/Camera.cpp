#include "Camera.h"
#include "Transform.h"
#include "Engine/Input.h"

Camera::Camera() : GameObject()
{
	mTarget = XMFLOAT3(0, 0, 0);
}

void Camera::OnInit()
{
	mTransform->SetPosition(1.0f, 1.0f, -5.0f);
}

void Camera::OnUpdate(float deltaTime)
{
	XMFLOAT3 tempdirz = XMFLOAT3(0, 0, 1);
	XMVECTOR dirz = XMLoadFloat3(&tempdirz);

	XMVECTOR rotation = XMLoadFloat4(&mTransform->GetRotation());

	XMVECTOR preTranslateDir = XMVector3Rotate(dirz, rotation);

	XMVECTOR dir = preTranslateDir + XMLoadFloat3(&mTransform->GetPosition());

	XMStoreFloat3(&mTarget, dir);
}

void Camera::OnDestroy()
{
	mRenderManager = Engine::GetInstance()->mRenderManager;
}

void Camera::OnCollision(GameObject* gt)
{
	
}

void Camera::OnUpdate(GameTimer* gt)
{
	mFrustum.CreateFromCamera(*this, mRenderManager->GetAspect(), mRenderManager->GetFovY(), mRenderManager->GetNearZ(), mRenderManager->GetFarZ());
}

void Camera::OnDestroy(GameTimer* gt)
{

}

XMFLOAT3 Camera::GetTarget()
{
	return mTarget;
}

XMMATRIX Camera::GetView()
{
	return XMMatrixLookAtLH(XMLoadFloat3(&mTransform->GetPosition()), XMLoadFloat3(&mTarget), XMVectorSet(0.0F, 1.0F, 0.0F, 0.0F));
}

Frustum Camera::GetFrustum()
{
	return mFrustum;
}
