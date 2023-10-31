#include "Camera.h"
#include "Transform.h"


Camera::Camera() : GameObject()
{

}

void Camera::OnInit()
{
	mTransform->SetPosition(0.0f, 0.0f, -2.0f);
}

void Camera::OnUpdate(float deltaTime)
{
	//mTransform->Translate(1 * gt->DeltaTime(), 0.0f, 0.0f);
	//mTransform->Rotate(0.1f,0.0f,0.0f);
}

void Camera::OnDestroy()
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