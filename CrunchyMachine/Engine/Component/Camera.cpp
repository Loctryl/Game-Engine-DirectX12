#include "Camera.h"
#include "Transform.h"
#include "Engine/Input.h"
#include "Frustum.h"

Camera::Camera() : GameObject()
{
	mTarget = XMFLOAT3(0, 0, 0);
	mRenderManager = Engine::GetInstance()->mRenderManager;
	mFrustum = new Frustum();
}

void Camera::OnInit()
{
	mTransform->SetPosition(0.0f, 0.0f, -2.0f);
}

void Camera::OnUpdate(float deltaTime)
{
	//XMFLOAT3 tempdirz = XMFLOAT3(0, 0, 1);
	//XMVECTOR dirz = XMLoadFloat3(&tempdirz);

	//XMVECTOR rotation = XMLoadFloat4(&mTransform->GetRotation());

	//XMVECTOR preTranslateDir = XMVector3Rotate(dirz, rotation);

	//XMVECTOR dir = preTranslateDir + XMLoadFloat3(&mTransform->GetPosition());

	mFrustum->CreateFromCamera(this, mRenderManager->GetAspect(), mRenderManager->GetFovY(), mRenderManager->GetNearZ(), mRenderManager->GetFarZ());

	//XMStoreFloat3(&mTarget, dir);
}

void Camera::OnDestroy()
{

}

void Camera::OnCollision(GameObject* gt)
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

Frustum* Camera::GetFrustum()
{
	return mFrustum;
}
