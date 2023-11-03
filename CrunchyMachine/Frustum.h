#include "Resources/framework.h"
#include "Engine/Component/Camera.h"

class Frustum
{
public:
	struct Plane
	{
		// unit vector
		XMFLOAT3 normal = { 0.f, 1.f, 0.f };

		// distance from origin to the nearest point in the plane
		float distance = 0.0f;

		float getSignedDistanceToPlane(XMFLOAT3& point)
		{
			float tempDistToPlane;
			XMStoreFloat(&tempDistToPlane, (XMLoadFloat3(&normal), XMLoadFloat3(&point)));
			tempDistToPlane -= distance;
			return tempDistToPlane;
		}
	};

	void CreateFromCamera(Camera& cam, float aspect, float fovY, float zNear, float zFar);
	Plane GetTopFace();
	Plane GetBottomFace();
	Plane GetRightFace();
	Plane GetLeftFace();
	Plane GetFarFace();
	Plane GetNearFace();

private:
	Plane mTopFace;
	Plane mBottomFace;

	Plane mRightFace;
	Plane mLeftFace;

	Plane mFarFace;
	Plane mNearFace;
};

