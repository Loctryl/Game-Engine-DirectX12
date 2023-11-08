#include "Camera.h"
#include "Transform.h"
#include "Engine/Input.h"
#include "Engine/ComponentManager/RenderManager.h"
#include "Window/Window.h"	
#include "DirectX12/D3DApp.h"

Camera::Camera() : GameObject()
{
	mTarget = XMFLOAT3(0, 0, 0);
	mRenderManager = Engine::GetInstance()->mRenderManager;
	CalculateProjMatrix();
}

void Camera::OnInit()
{

}

void Camera::OnUpdate(float deltaTime)
{

}

void Camera::OnDestroy()
{

}

void Camera::OnCollision(GameObject* gt)
{
	
}

void Camera::SetTarget(XMFLOAT3 newTarget)
{
	mTarget = newTarget;
}

XMFLOAT3 Camera::GetTarget() { return mTarget; }

void Camera::CalculateProjMatrix()
{
	XMStoreFloat4x4(&mProjMatrix, XMMatrixPerspectiveFovLH(XMConvertToRadians(mFovY), RenderManager::GetAspectRatio(), mNearZ, mFarZ));
}

void Camera::CalculateOrthoProjMatrix()
{
	XMStoreFloat4x4(&mOrthoProjMatrix, XMMatrixOrthographicLH(RenderManager::GetClientWidth(), RenderManager::GetClientHeight(), mNearZ, mFarZ));
}

XMMATRIX Camera::GetView()
{
	//XMFLOAT3 dir = XMFLOAT3(1.0f, 0.0f, 0.0f);
	//return XMMatrixLookAtLH(XMLoadFloat3(&mParent->mTransform->GetPosition()), XMLoadFloat3(&mTarget), XMVectorSet(0.0F, 1.0F, 0.0F, 0.0F));
	mTransform->CalcSuperWorldMatrix();
	return XMMatrixInverse( &XMMatrixDeterminant(XMLoadFloat4x4(&mTransform->GetSuperWorldMatrix())), XMLoadFloat4x4(&mTransform->GetSuperWorldMatrix()));
}

XMMATRIX Camera::GetOrthoView()
{
	XMFLOAT3 pos = XMFLOAT3(0.f, 0.f, -2.0f);
	XMFLOAT3 targ = XMFLOAT3(0.f, 0.f, 0.f);
	return XMMatrixLookAtLH(XMLoadFloat3(&pos), XMLoadFloat3(&targ), XMVectorSet(0.0F, 1.0F, 0.0F, 0.0F));
}

XMFLOAT4X4 Camera::GetProj() { return mProjMatrix; }

XMFLOAT4X4 Camera::GetViewProj() 
{
	XMFLOAT4X4 viewProj;
	XMStoreFloat4x4(&viewProj, GetView() * XMLoadFloat4x4(&mProjMatrix));
	return viewProj;
}

XMFLOAT4X4 Camera::GetViewProjTranspose()
{
	XMFLOAT4X4 viewProj;
	XMStoreFloat4x4(&viewProj, XMMatrixTranspose(GetView() * XMLoadFloat4x4(&mProjMatrix)));
	return viewProj;
}


XMFLOAT4X4 Camera::GetOrthoProj() { return mOrthoProjMatrix; }

XMFLOAT4X4 Camera::GetOrthoViewProj()
{
	XMFLOAT4X4 viewProj;
	XMStoreFloat4x4(&viewProj, GetOrthoView() * XMLoadFloat4x4(&mOrthoProjMatrix));
	return viewProj;
}

XMFLOAT4X4 Camera::GetOrthoViewProjTranspose()
{
	XMFLOAT4X4 viewProj;
	XMStoreFloat4x4(&viewProj, XMMatrixTranspose(GetOrthoView() * XMLoadFloat4x4(&mOrthoProjMatrix)));
	return viewProj;
}