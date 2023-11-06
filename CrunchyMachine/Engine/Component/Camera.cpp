#include "Camera.h"
#include "Transform.h"
#include "Engine/Input.h"
#include "Engine/GameObject.h"
#include "Window/Window.h"	

Camera::Camera() : Script()
{
	mTarget = XMFLOAT3(0, 0, 0);
	mInput = Input::GetInstance();
}

void Camera::OnInit()
{
	mGameObject->mTransform->SetPosition(1.0f, 6.0f, -50.0f);
}

void Camera::OnUpdate(float deltaTime)
{
	mInput->GetMousePosition(Window::GetHWND());


	switch (static_cast<int>(mInput->GetInputStates()[0])) {
	case 3:
		mGameObject->mTransform->Translate(0, 0, 4 * deltaTime);
		break;
	default:
		break;
	}
	switch (static_cast<int>(mInput->GetInputStates()[1])) {
	case 3:
		mGameObject->mTransform->Translate(-4 * deltaTime, 0, 0);
		break;
	default:
		break;
	}
	switch (static_cast<int>(mInput->GetInputStates()[2])) {
	case 3:
		mGameObject->mTransform->Translate(0, 0, -4 * deltaTime);
		break;
	default:
		break;
	}
	switch (static_cast<int>(mInput->GetInputStates()[3])) {
	case 3:
		mGameObject->mTransform->Translate(4 * deltaTime, 0, 0);
		break;
	default:
		break;
	}


	XMFLOAT3 tempdirz = XMFLOAT3(0, 0, 1);
	XMVECTOR dirz = XMLoadFloat3(&tempdirz);

	XMVECTOR rotation = XMLoadFloat4(&mGameObject->mTransform->GetRotation());

	XMVECTOR preTranslateDir = XMVector3Rotate(dirz, rotation);

	XMVECTOR dir = preTranslateDir + XMLoadFloat3(&mGameObject->mTransform->GetPosition());

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
	return XMMatrixLookAtLH(XMLoadFloat3(&mGameObject->mTransform->GetPosition()), XMLoadFloat3(&mTarget), XMVectorSet(0.0F, 1.0F, 0.0F, 0.0F));
}