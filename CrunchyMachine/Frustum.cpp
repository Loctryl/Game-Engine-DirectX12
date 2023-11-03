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