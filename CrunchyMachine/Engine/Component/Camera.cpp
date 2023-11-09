#include "Camera.h"
#include "Transform.h"
#include "Engine/ComponentManager/RenderManager.h"
#include "DirectX12/D3DApp.h"

Camera::Camera() : GameObject()
{
	mTarget = XMFLOAT3(0, 0, 0);
	mRenderManager = Engine::GetInstance()->mRenderManager;
	CalculateProjMatrix();
}

Camera::~Camera() { mRenderManager = nullptr; }

void Camera::OnInit() { }

void Camera::OnUpdate(float deltaTime) { }

void Camera::OnDestroy() { }

void Camera::OnCollision(GameObject* go) { }

void Camera::CalculateProjMatrix()
{
	XMStoreFloat4x4(&mProjMatrix, XMMatrixPerspectiveFovLH(XMConvertToRadians(mFovY), RenderManager::GetAspectRatio(), mNearZ, mFarZ));
}

void Camera::CalculateOrthoProjMatrix()
{
	XMStoreFloat4x4(&mOrthoProjMatrix, XMMatrixOrthographicLH(RenderManager::GetClientWidth(), RenderManager::GetClientHeight(), mNearZ, mFarZ));
}

XMMATRIX Camera::GetView() const
{
	mTransform->CalcSuperWorldMatrix();
	return XMMatrixInverse( &XMMatrixDeterminant(XMLoadFloat4x4(&mTransform->GetSuperWorldMatrix())), XMLoadFloat4x4(&mTransform->GetSuperWorldMatrix()));
}

XMMATRIX Camera::GetOrthoView() const
{
	XMFLOAT3 pos = XMFLOAT3(0.f, 0.f, -2.0f);
	XMFLOAT3 targ = XMFLOAT3(0.f, 0.f, 0.f);
	return XMMatrixLookAtLH(XMLoadFloat3(&pos), XMLoadFloat3(&targ), XMVectorSet(0.0F, 1.0F, 0.0F, 0.0F));
}

XMFLOAT4X4 Camera::GetViewProj() const
{
	XMFLOAT4X4 viewProj;
	XMStoreFloat4x4(&viewProj, GetView() * XMLoadFloat4x4(&mProjMatrix));
	return viewProj;
}

XMFLOAT4X4 Camera::GetViewProjTranspose() const
{
	XMFLOAT4X4 viewProj;
	XMStoreFloat4x4(&viewProj, XMMatrixTranspose(GetView() * XMLoadFloat4x4(&mProjMatrix)));
	return viewProj;
}

XMFLOAT4X4 Camera::GetOrthoViewProj() const
{
	XMFLOAT4X4 viewProj;
	XMStoreFloat4x4(&viewProj, GetOrthoView() * XMLoadFloat4x4(&mOrthoProjMatrix));
	return viewProj;
}

XMFLOAT4X4 Camera::GetOrthoViewProjTranspose() const
{
	XMFLOAT4X4 viewProj;
	XMStoreFloat4x4(&viewProj, XMMatrixTranspose(GetOrthoView() * XMLoadFloat4x4(&mOrthoProjMatrix)));
	return viewProj;
}