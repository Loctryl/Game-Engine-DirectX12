#include "Camera.h"
#include "Transform.h"


Camera::Camera()
{

}

void Camera::OnInit(GameTimer* gt)
{

}

void Camera::OnUpdate(GameTimer* gt)
{
	mTransform->Translate(1 * gt->DeltaTime(), 0.0f, 0.0f);
	//mTransform->Rotate(0.1f,0.0f,0.0f);
}

void Camera::OnDestroy(GameTimer* gt)
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