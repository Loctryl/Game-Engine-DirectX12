#pragma once
#include "Resources/framework.h"
#include "Frustum.h"


class FrustumCulling
{
private:
	XMFLOAT3 Center; // Center of the box.
	XMFLOAT3 Extents; // Distance from the center to each side.


public:
	bool isOnFrustum(Frustum& camFrustum, Transform& transform);
};

struct AABB : Frustum
{
	XMFLOAT3 center =  XMFLOAT3(0.f, 0.f, 0.f);
	XMFLOAT3 extents{ 0.f, 0.f, 0.f };

	AABB(XMFLOAT3& min, XMFLOAT3& max)
	{
		XMStoreFloat3(&center, (XMLoadFloat3(&max) + XMLoadFloat3(&min)) * 0.5f);
		extents = XMFLOAT3(max.x - center.x, max.y - center.y, max.z - center.z);
	};

	AABB(XMFLOAT3& inCenter, float iI, float iJ, float iK) 
	{
		center = inCenter;
		extents = XMFLOAT3(iI, iJ, iK);
	}

	AABB(XMVECTOR& inCenter, float iI, float iJ, float iK)
	{
		XMStoreFloat3(&center, inCenter);
		extents = XMFLOAT3(iI, iJ, iK);
	}

	bool isOnOrForwardPlane(Plane& plane)
	{
		// Compute the projection interval radius of b onto L(t) = b.c + t * p.n
		const float r = extents.x * std::abs(plane.normal.x) +
			extents.y * std::abs(plane.normal.y) + extents.z * std::abs(plane.normal.z);

		return -r <= plane.getSignedDistanceToPlane(center);
	}
};
