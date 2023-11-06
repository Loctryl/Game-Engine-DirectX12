#include "Frustum.h"
#include "Engine/Component/Transform.h"

bool BoundingSphere::isOnFrustum(Frustum* frust, Transform* trans)
{
	XMFLOAT3 gScale = trans->GetScale();

	XMVECTOR gCenter{ XMVector3Transform(XMLoadFloat4(&XMFLOAT4(center.x, center.y, center.z,1.f)),XMLoadFloat4x4(&trans->GetWorldMatrix())) };

	float maxScale = max(max(gScale.x, gScale.y), gScale.z);

	BoundingSphere gShere(gCenter, radius * (maxScale * 0.5f));

	return (gShere.isOnOrForwardPlane(&frust->mLeftFace) &&
		gShere.isOnOrForwardPlane(&frust->mRightFace) &&
		gShere.isOnOrForwardPlane(&frust->mTopFace) &&
		gShere.isOnOrForwardPlane(&frust->mBottomFace) &&
		gShere.isOnOrForwardPlane(&frust->mNearFace) &&
		gShere.isOnOrForwardPlane(&frust->mFarFace));
}

bool BoundingBox::isOnFrustum(Frustum* frust, Transform* trans)
{
	//Get global scale thanks to our transform
	XMVECTOR gCenter = XMVector3Transform(XMLoadFloat4(&XMFLOAT4(center.x, center.y, center.z, 1.0f)), XMLoadFloat4x4(&trans->GetWorldMatrix()));

	// Scaled orientation
	XMVECTOR right = XMLoadFloat3(&trans->GetDirectionX());
	right *= extends.x;
	XMVECTOR up = XMLoadFloat3(&trans->GetDirectionY());
	up *= extends.y;
	XMVECTOR forward = XMLoadFloat3(&trans->GetDirectionZ());
	forward *= extends.z;

	XMFLOAT3 globalX = XMFLOAT3(1.0f, 0.0f, 0.0f);
	float newIi;

	XMStoreFloat(&newIi,
		XMVectorAbs(XMVector3Dot(XMLoadFloat3(&globalX), right)) +
		XMVectorAbs(XMVector3Dot(XMLoadFloat3(&globalX), up)) +
		XMVectorAbs(XMVector3Dot(XMLoadFloat3(&globalX), forward)));

	XMFLOAT3 globalY = XMFLOAT3(0.0f, 1.0f, 0.0f);;
	float newIj;

	XMStoreFloat(&newIj,
		XMVectorAbs(XMVector3Dot(XMLoadFloat3(&globalY), right)) +
		XMVectorAbs(XMVector3Dot(XMLoadFloat3(&globalY), up)) +
		XMVectorAbs(XMVector3Dot(XMLoadFloat3(&globalY), forward)));

	XMFLOAT3 globalZ = XMFLOAT3(0.0f, 0.0f, 1.0f);;
	float newIk;

	XMStoreFloat(&newIk,
		XMVectorAbs(XMVector3Dot(XMLoadFloat3(&globalZ), right)) +
		XMVectorAbs(XMVector3Dot(XMLoadFloat3(&globalZ), up)) +
		XMVectorAbs(XMVector3Dot(XMLoadFloat3(&globalZ), forward)));

	//We not need to divise scale because it's based on the half extention of the AABB
	BoundingBox gBox(gCenter, XMFLOAT3(newIi, newIj, newIk));

	return (gBox.isOnOrForwardPlane(&frust->mLeftFace) &&
		gBox.isOnOrForwardPlane(&frust->mRightFace) &&
		gBox.isOnOrForwardPlane(&frust->mTopFace) &&
		gBox.isOnOrForwardPlane(&frust->mBottomFace) &&
		gBox.isOnOrForwardPlane(&frust->mNearFace) &&
		gBox.isOnOrForwardPlane(&frust->mFarFace));
}