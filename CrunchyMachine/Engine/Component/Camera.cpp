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
	mInput = Input::GetInstance();
	CalculateProjMatrix();
}

void Camera::OnInit()
{
	mFrustum = CalcFrustum(RenderManager::GetAspectRatio(), mFovY, mNearZ, mFarZ);
	mTransform->SetPosition(0.0f, 1.0f, -5.0f);
}

void Camera::OnUpdate(float deltaTime)
{
	//Rotate the cam in function of the mouse pos and the screen center
	XMVECTOR mousePos = XMLoadFloat2(&mInput->GetMousePosition(Window::GetHWND()));  
	XMVECTOR screenSize = XMLoadFloat2(&D3DApp::GetInstance()->GetWindowSize());
	XMFLOAT2 tempMousePos;
	XMStoreFloat2( &tempMousePos, mousePos - (screenSize/2));

	XMFLOAT3 centeredMousPos = XMFLOAT3(tempMousePos.x, tempMousePos.y, 0);
	XMVECTOR tempDir = XMLoadFloat3(&mTransform->GetDirz());
	tempDir += XMLoadFloat3(&centeredMousPos);
	XMVector3Normalize(tempDir);
	tempDir /= 5000;

	XMFLOAT3 almostFinalDir;
	XMStoreFloat3(&almostFinalDir, tempDir);
	XMFLOAT3 finalDir = XMFLOAT3(almostFinalDir.y, almostFinalDir.x, almostFinalDir.z);
	mTransform->Rotate(finalDir);

	//recenter Cursor
	RECT r;
	GetWindowRect(Window::GetHWND(), &r);
	SetCursorPos((D3DApp::GetInstance()->GetWindowSize().x / 2) + r.left +8, (D3DApp::GetInstance()->GetWindowSize().y / 2) + r.top +31);

	//get the inputs to move the cam
	switch (static_cast<int>(mInput->GetInputStates()[0])) {
	case 3:
		mTransform->Translate(0, 0, 9 * deltaTime);
		break;
	default:
		break;
	}
	switch (static_cast<int>(mInput->GetInputStates()[1])) {
	case 3:
		mTransform->Translate(-9 * deltaTime, 0, 0);
		break;
	default:
		break;
	}
	switch (static_cast<int>(mInput->GetInputStates()[2])) {
	case 3:
		mTransform->Translate(0, 0, -9 * deltaTime);
		break;
	default:
		break;
	}
	switch (static_cast<int>(mInput->GetInputStates()[3])) {
	case 3:
		mTransform->Translate(9 * deltaTime, 0, 0);
		break;
	default:
		break;
	}

	//Calculate the new focus of the camera in function of it's direction
	XMFLOAT3 tempdirz = mTransform->GetDirz();
	XMVECTOR dirz = XMLoadFloat3(&tempdirz);
	XMVECTOR rotation = XMLoadFloat4(&mTransform->GetRotation());
	XMVECTOR preTranslateDir = XMVector3Rotate(dirz, rotation);
	XMVECTOR dir = preTranslateDir + XMLoadFloat3(&mTransform->GetPosition());
	XMStoreFloat3(&mTarget, dir);


	mFrustum = CalcFrustum(RenderManager::GetAspectRatio(), mFovY, mNearZ, mFarZ);
}

void Camera::OnDestroy()
{

}

void Camera::OnCollision(GameObject* gt)
{
	
}

XMFLOAT3 Camera::GetTarget() { return mTarget; }

void Camera::CalculateProjMatrix()
{
	XMStoreFloat4x4(&mProjMatrix, XMMatrixPerspectiveFovLH(XMConvertToRadians(mFovY), RenderManager::GetAspectRatio(), mNearZ, mFarZ));
}

XMMATRIX Camera::GetView()
{
	return XMMatrixLookAtLH(XMLoadFloat3(&mTransform->GetPosition()), XMLoadFloat3(&mTarget), XMVectorSet(0.0F, 1.0F, 0.0F, 0.0F));
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