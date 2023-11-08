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
	mFrustum = Frustum();
	CalculateProjMatrix();
}

void Camera::OnInit()
{
	mFrustum = CalcFrustum(RenderManager::GetAspectRatio(), mFovY, mNearZ, mFarZ);
	//mTransform->SetPosition(0.0f, 0.0f, -50.0f);
}

void Camera::OnUpdate(float deltaTime)
{
	mFrustum = CalcFrustum(RenderManager::GetAspectRatio(), mFovY, mNearZ, mFarZ);
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
	return XMMatrixLookAtLH(XMLoadFloat3(&mTransform->GetPosition()), XMLoadFloat3(&mTarget), XMVectorSet(0.0F, 1.0F, 0.0F, 0.0F));
}

XMMATRIX Camera::GetOrthoView()
{
	XMFLOAT3 pos = XMFLOAT3(0.f, 0.f, -1.0f);
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

Frustum* Camera::GetFrustum() { return &mFrustum; }

Frustum Camera::CalcFrustum(float aspect, float fovY, float zNear, float zFar) 
{
    Frustum frust;
    float halfVSide = zFar * tanf(XMConvertToRadians(fovY * 0.5f));
    float halfHSide = halfVSide * aspect;

    XMVECTOR pos = DirectX::XMLoadFloat3(&mTransform->GetPosition());
    XMVECTOR right = DirectX::XMLoadFloat3(&mTransform->GetDirectionX());
    XMVECTOR up = DirectX::XMLoadFloat3(&mTransform->GetDirectionY());
    XMVECTOR front = DirectX::XMLoadFloat3(&mTransform->GetDirectionZ());

    XMVECTOR frontMultFar = zFar * front;

    frust.mNearFace = { pos + (zNear * front), front };

    frust.mFarFace = { pos + frontMultFar, -front };

    frust.mRightFace = { pos, XMVector3Cross(frontMultFar + right * halfHSide, up) };

    frust.mLeftFace = { pos, XMVector3Cross(up, frontMultFar - right * halfHSide) };

    frust.mTopFace = { pos, XMVector3Cross(right, frontMultFar + up * halfVSide) };
    
    frust.mBottomFace = { pos, XMVector3Cross(frontMultFar - up * halfVSide, right) };

    return frust;
}