#include "Camera.h"
#include "Transform.h"
#include "Engine/Input.h"
#include "Window/Window.h"	

Camera::Camera() : GameObject()
{
	mTarget = XMFLOAT3(0, 0, 0);
	mInput = Input::GetInstance();
}

void Camera::OnInit()
{
	mTransform->SetPosition(1.0f, 1.0f, -5.0f);
}

void Camera::OnUpdate(float deltaTime)
{
	mInput->GetMousePosition(Window::GetHWND());


	switch (static_cast<int>(mInput->GetInputStates()[0])) {
	case 3:
		mTransform->Translate(0, 0, 1 * deltaTime);
		break;
	default:
		break;
	}
	switch (static_cast<int>(mInput->GetInputStates()[1])) {
	case 3:
		mTransform->Translate(-1 * deltaTime, 0, 0);
		break;
	default:
		break;
	}
	switch (static_cast<int>(mInput->GetInputStates()[2])) {
	case 3:
		mTransform->Translate(0, 0, -1 * deltaTime);
		break;
	default:
		break;
	}
	switch (static_cast<int>(mInput->GetInputStates()[3])) {
	case 3:
		mTransform->Translate(1 * deltaTime, 0, 0);
		break;
	default:
		break;
	}


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