#include "Frustum.h"
#include "Engine/Component/Transform.h"

void Frustum::CreateFromCamera(Camera& cam, float aspect, float fovY, float zNear, float zFar)
{
    float halfVSide = zFar * tanf(fovY * 0.5f);
    float halfHSide = halfVSide * aspect;

    XMVECTOR tempPos = XMLoadFloat3(&cam.mTransform->GetPosition());
    XMVECTOR tempDirX = XMLoadFloat3(&cam.mTransform->GetDirectionX());
    XMVECTOR tempDirY = XMLoadFloat3(&cam.mTransform->GetDirectionY());
    XMVECTOR tempDirZ = XMLoadFloat3(&cam.mTransform->GetDirectionZ());

    XMVECTOR frontMultFar = zFar * tempDirZ;

    XMStoreFloat3(&mNearFace.normal, tempPos + zNear * tempDirZ);
    XMStoreFloat(&mNearFace.distance, tempDirZ);

    XMStoreFloat3(&mFarFace.normal, tempPos + frontMultFar);
    XMStoreFloat(&mNearFace.distance, -tempDirZ);

    XMStoreFloat3(&mRightFace.normal, tempPos);
    XMStoreFloat(&mRightFace.distance, XMVector3Cross(frontMultFar - tempDirX * halfHSide, tempDirY));

    XMStoreFloat3(&mLeftFace.normal, tempPos);
    XMStoreFloat(&mLeftFace.distance, XMVector3Cross(tempDirY, frontMultFar + tempDirX * halfHSide));

    XMStoreFloat3(&mTopFace.normal, tempPos);
    XMStoreFloat(&mTopFace.distance, XMVector3Cross(tempDirX, frontMultFar - tempDirY * halfVSide));

    XMStoreFloat3(&mBottomFace.normal, tempPos);
    XMStoreFloat(&mBottomFace.distance, XMVector3Cross(frontMultFar + tempDirY * halfVSide, tempDirX));
}

Frustum::Plane Frustum::GetTopFace()
{
    return mTopFace;
}

Frustum::Plane Frustum::GetBottomFace()
{
    return mBottomFace;
}

Frustum::Plane Frustum::GetRightFace()
{
    return mRightFace;
}

Frustum::Plane Frustum::GetLeftFace()
{
    return mLeftFace;
}

Frustum::Plane Frustum::GetFarFace()
{
    return mFarFace;
}

Frustum::Plane Frustum::GetNearFace()
{
    return mNearFace;
}
