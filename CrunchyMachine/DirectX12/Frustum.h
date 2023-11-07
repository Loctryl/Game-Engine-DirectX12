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


class BoundingVolume
{
public:
	virtual bool isOnFrustum(Frustum* frust, Transform* modelTrans) = 0;
};

struct BoundingSkyBox : public BoundingVolume
{
	virtual bool isOnFrustum(Frustum* frust, Transform* modelTrans) { return true; }
};

struct BoundingSphere : public BoundingVolume
{
	XMFLOAT3 center{ 0.0f,0.0f,0.0f };
	float radius{ 2.0f };

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

struct BoundingBox : public BoundingVolume
{
	XMFLOAT3 center{ 0.0f,0.0f,0.0f };
	XMFLOAT3 extends{ 2.f, 2.f, 2.f };

	BoundingBox() = default;

	BoundingBox(XMFLOAT3 e) { extends = e; }

	BoundingBox(XMVECTOR max, XMVECTOR min)
	{
		XMStoreFloat3(&center, (max + min) * 0.5f);
		XMStoreFloat3(&extends, (max + min) * 0.5f);
		extends.x = XMVectorGetX(max) - center.x;
		extends.y = XMVectorGetY(max) - center.y;
		extends.z = XMVectorGetZ(max) - center.z;
	}

	BoundingBox(XMVECTOR c, XMFLOAT3 e)
	{
		XMStoreFloat3(&center, c);
		extends = e;
	}

	virtual bool isOnFrustum(Frustum* frust, Transform* modelTrans);

	bool isOnOrForwardPlane(Plane* plane)
	{
		const float r = extends.x * std::abs(plane->normal.x)
			+ extends.y * std::abs(plane->normal.y)
			+ extends.z * std::abs(plane->normal.z);

		return -r <= plane->getSignedDistanceToPlane(center);
	}
};