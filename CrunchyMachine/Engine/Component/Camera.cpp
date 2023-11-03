#include "Camera.h"
#include "Transform.h"
#include "Engine/Input.h"
#include "Engine/ComponentManager/RenderManager.h"

Camera::Camera() : GameObject()
{
	mTarget = XMFLOAT3(0, 0, 0);
}

void Camera::OnInit()
{
	CalculateProjMatrix();
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

}

void Camera::CalculateProjMatrix()
{
	XMStoreFloat4x4(&mProjMatrix, XMMatrixPerspectiveFovLH(XMConvertToRadians(80.0F), RenderManager::GetAspectRatio(), 0.05F, 1000.0F));
}

XMFLOAT3 Camera::GetTarget()
{
	return mTarget;
}

XMMATRIX Camera::GetView()
{
	return XMMatrixLookAtLH(XMLoadFloat3(&mTransform->GetPosition()), XMLoadFloat3(&mTarget), XMVectorSet(0.0F, 1.0F, 0.0F, 0.0F));
}

XMFLOAT4X4 Camera::GetProj() { return mProjMatrix; }

XMFLOAT4X4 Camera::GetViewProj() {
	XMFLOAT4X4 viewProj;

	XMStoreFloat4x4(&viewProj, GetView() * XMLoadFloat4x4(&mProjMatrix));

	return viewProj;
}