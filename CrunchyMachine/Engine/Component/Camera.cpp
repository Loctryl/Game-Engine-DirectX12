#include "Camera.h"
#include "Transform.h"
#include "Engine/Input.h"
#include "Window/Window.h"	
#include "DirectX12/D3DApp.h"

Camera::Camera() : GameObject()
{
	mTarget = XMFLOAT3(0, 0, 0);
	mInput = Input::GetInstance();
}

void Camera::OnInit()
{
	mTransform->SetPosition(1.0f, 6.0f, -50.0f);
}

void Camera::OnUpdate(float deltaTime)
{

	XMVECTOR mousePos = XMLoadFloat2(&mInput->GetMousePosition(Window::GetHWND()));  
	XMVECTOR screenSize = XMLoadFloat2(&D3DApp::GetInstance()->GetWindowSize());
	XMFLOAT2 tempMousePos;
	XMStoreFloat2( &tempMousePos, mousePos - (screenSize / 2));

	XMFLOAT3 centeredMousPos = XMFLOAT3(tempMousePos.x, tempMousePos.y, 0);
	XMVECTOR tempDir = XMLoadFloat3(&mTransform->GetDirz());
	tempDir += XMLoadFloat3(&centeredMousPos);
	tempDir /= 50000;

	XMFLOAT3 almostFinalDir;
	XMStoreFloat3(&almostFinalDir, tempDir);
	XMFLOAT3 finalDir = XMFLOAT3(almostFinalDir.y, almostFinalDir.x, almostFinalDir.z);
	mTransform->Rotate(finalDir);


	//mTransform->Rotate();

	cout << tempMousePos.x << "," << tempMousePos.y<<"  ;  ";

	switch (static_cast<int>(mInput->GetInputStates()[0])) {
	case 3:
		mTransform->Translate(0, 0, 4 * deltaTime);
		break;
	default:
		break;
	}
	switch (static_cast<int>(mInput->GetInputStates()[1])) {
	case 3:
		mTransform->Translate(-4 * deltaTime, 0, 0);
		break;
	default:
		break;
	}
	switch (static_cast<int>(mInput->GetInputStates()[2])) {
	case 3:
		mTransform->Translate(0, 0, -4 * deltaTime);
		break;
	default:
		break;
	}
	switch (static_cast<int>(mInput->GetInputStates()[3])) {
	case 3:
		mTransform->Translate(4 * deltaTime, 0, 0);
		break;
	default:
		break;
	}


	XMFLOAT3 tempdirz = mTransform->GetDirz();
	XMVECTOR dirz = XMLoadFloat3(&tempdirz);

	XMVECTOR rotation = XMLoadFloat4(&mTransform->GetRotation());

	XMVECTOR preTranslateDir = XMVector3Rotate(dirz, rotation);

	XMVECTOR dir = preTranslateDir + XMLoadFloat3(&mTransform->GetPosition());

	XMStoreFloat3(&mTarget, dir);
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