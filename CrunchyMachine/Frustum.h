#pragma once
#include "EngineResources/framework.h"

class Camera;

struct Plane
{
	Plane() = default;
	// unit vector
	XMFLOAT3 normal = { 0.f, 1.f, 0.f };

	// distance from origin to the nearest point in the plane
	float distance = 0.0f;

	float getSignedDistanceToPlane(XMFLOAT3& point)
	{
		float tempDistToPlane;
		DirectX::XMStoreFloat(&tempDistToPlane, (DirectX::XMLoadFloat3(&normal), DirectX::XMLoadFloat3(&point)));
		tempDistToPlane -= distance;
		return tempDistToPlane;
	}
};

class Frustum
{
public:
	Frustum();

	void CreateFromCamera(Camera* cam, float aspect, float fovY, float zNear, float zFar);
	Plane* GetTopFace();
	Plane* GetBottomFace();
	Plane* GetRightFace();
	Plane* GetLeftFace();
	Plane* GetFarFace();
	Plane* GetNearFace();

private:
	Plane* mTopFace;
	Plane* mBottomFace;

	Plane* mRightFace;
	Plane* mLeftFace;

	Plane* mFarFace;
	Plane* mNearFace;
	//std::vector<Plane*> mPlanes;
};

