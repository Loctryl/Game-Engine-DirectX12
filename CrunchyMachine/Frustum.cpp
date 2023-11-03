#include "Frustum.h"
#include "Engine/Component/Transform.h"
#include "Engine/Component/Camera.h"



Frustum::Frustum()
{
    mTopFace = new Plane();
    mBottomFace = new Plane();

    mRightFace = new Plane();
    mLeftFace = new Plane();

    mFarFace = new Plane();
    mNearFace = new Plane();

    //mPlanes.push_back(new Plane());
}

void Frustum::CreateFromCamera(Camera* cam, float aspect, float fovY, float zNear, float zFar)
{
    float halfVSide = zFar * tanf(fovY * 0.5f);
    float halfHSide = halfVSide * aspect;

    XMVECTOR tempPos = DirectX::XMLoadFloat3(&cam->mTransform->GetPosition());
    XMVECTOR tempDirX = DirectX::XMLoadFloat3(&cam->mTransform->GetDirectionX());
    XMVECTOR tempDirY = DirectX::XMLoadFloat3(&cam->mTransform->GetDirectionY());
    XMVECTOR tempDirZ = DirectX::XMLoadFloat3(&cam->mTransform->GetDirectionZ());

    XMVECTOR frontMultFar = zFar * tempDirZ;

    DirectX::XMStoreFloat3(&mNearFace->normal, tempPos + (zNear * tempDirZ));
    DirectX::XMStoreFloat(&mNearFace->distance, tempDirZ);

    DirectX::XMStoreFloat3(&mFarFace->normal, tempPos + frontMultFar);
    DirectX::XMStoreFloat(&mNearFace->distance, -tempDirZ);

    DirectX::XMStoreFloat3(&mRightFace->normal, tempPos);
    DirectX::XMStoreFloat(&mRightFace->distance, XMVector3Cross(frontMultFar - tempDirX * halfHSide, tempDirY));

    DirectX::XMStoreFloat3(&mLeftFace->normal, tempPos);
    DirectX::XMStoreFloat(&mLeftFace->distance, XMVector3Cross(tempDirY, frontMultFar + tempDirX * halfHSide));

    DirectX::XMStoreFloat3(&mTopFace->normal, tempPos);
    DirectX::XMStoreFloat(&mTopFace->distance, XMVector3Cross(tempDirX, frontMultFar - tempDirY * halfVSide));

    DirectX::XMStoreFloat3(&mBottomFace->normal, tempPos);
    DirectX::XMStoreFloat(&mBottomFace->distance, XMVector3Cross(frontMultFar + tempDirY * halfVSide, tempDirX));
}

Plane* Frustum::GetTopFace()
{
    return mTopFace;
}

Plane* Frustum::GetBottomFace()
{
    return mBottomFace;
}

Plane* Frustum::GetRightFace()
{
    return mRightFace;
}

Plane* Frustum::GetLeftFace()
{
    return mLeftFace;
}

Plane* Frustum::GetFarFace()
{
    return mFarFace;
}

Plane* Frustum::GetNearFace()
{
    return mNearFace;
}
