#pragma once
#include "EngineResources/framework.h"

class Camera;
class Transform;

struct Plane
{
	Plane() = default;
	Plane(XMVECTOR p, XMVECTOR n)
	{
		XMStoreFloat3(&normal, XMVector3Normalize(n));
		distance = XMVectorGetX(XMVector3Dot(p, XMLoadFloat3(&normal)));
	}
	// unit vector
	XMFLOAT3 normal = { 0.f, 0.f, 0.f };

	// distance from origin to the nearest point in the plane
	float distance = 0.0f;

	float getSignedDistanceToPlane(XMFLOAT3 point)
	{
		return XMVectorGetX(XMVector3Dot(XMLoadFloat3(&normal), XMLoadFloat3(&point))) - distance;
	}
};

struct Frustum
{
	Plane mTopFace;
	Plane mBottomFace;

	Plane mRightFace;
	Plane mLeftFace;

	Plane mFarFace;
	Plane mNearFace;
};


struct BoundingVolume
{
	virtual bool isOnFrustum(Frustum* frust, Transform* modelTrans) = 0;
};

struct BoundingSphere : public BoundingVolume
{
	XMFLOAT3 center{ 0.0f,0.0f,0.0f };
	float radius{ 1.0f };

	BoundingSphere() = default;

	BoundingSphere(XMVECTOR c, float r) 
	{
		XMStoreFloat3(&center, c);
		radius = r;
	}

	virtual bool isOnFrustum(Frustum* frust, Transform* modelTrans);

	bool isOnOrForwardPlane(Plane* plane)
	{
		return plane->getSignedDistanceToPlane(center) > -radius;
	}
};