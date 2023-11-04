#include "Camera.h"
#include "Transform.h"
#include "Engine/Input.h"
#include "Engine/ComponentManager/RenderManager.h"

Camera::Camera() : GameObject()
{
	mTarget = XMFLOAT3(0, 0, 0);
	mRenderManager = Engine::GetInstance()->mRenderManager;
	mFrustum = Frustum();
	mInput = Input::GetInstance();
}

void Camera::OnInit()
{
	mFrustum = CalcFrustum(mRenderManager->GetAspect(), mRenderManager->GetFovY(), mRenderManager->GetNearZ(), mRenderManager->GetFarZ());
	CalculateProjMatrix();
	mTransform->SetPosition(0.0f, 1.0f, -5.0f);
}

void Camera::OnUpdate(float deltaTime)
{
	//XMFLOAT3 tempdirz = XMFLOAT3(0, 0, 1);
	//XMVECTOR dirz = XMLoadFloat3(&tempdirz);

	//XMVECTOR rotation = XMLoadFloat4(&mTransform->GetRotation());

	//XMVECTOR preTranslateDir = XMVector3Rotate(dirz, rotation);

	//XMVECTOR dir = preTranslateDir + XMLoadFloat3(&mTransform->GetPosition());

	//XMStoreFloat3(&mTarget, dir);

	switch (static_cast<int>(mInput->GetInputStates()[0])) {
	case 3:
		mTransform->Rotate(-1 * deltaTime, 0, 0);
		mTarget.y += 1 * deltaTime * 5;
		break;
	default:
		break;
	}
	switch (static_cast<int>(mInput->GetInputStates()[1])) {
	case 3:
		mTransform->Rotate(0, -1 * deltaTime, 0);
		mTarget.x += -1 * deltaTime * 5;
		break;
	default:
		break;
	}
	switch (static_cast<int>(mInput->GetInputStates()[2])) {
	case 3:
		mTransform->Rotate(1 * deltaTime, 0, 0);
		mTarget.y += -1 * deltaTime * 5;
		break;
	default:
		break;
	}
	switch (static_cast<int>(mInput->GetInputStates()[3])) {
	case 3:
		mTransform->Rotate(0, 1 * deltaTime, 0);
		mTarget.x += 1 * deltaTime * 5;
		break;
	default:
		break;
	}

	mFrustum = CalcFrustum(mRenderManager->GetAspect(), mRenderManager->GetFovY(), mRenderManager->GetNearZ(), mRenderManager->GetFarZ());

	mTransform->CalcWorldMatrix();
}

void Camera::OnDestroy()
{

}

void Camera::OnCollision(GameObject* gt)
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

Frustum* Camera::GetFrustum()
{
	return &mFrustum;
}

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