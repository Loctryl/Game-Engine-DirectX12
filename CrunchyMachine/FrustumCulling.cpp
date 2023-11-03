#include "FrustumCulling.h"
#include "Engine/Component/Transform.h"

//bool BoundingBox::isOnFrustum(Frustum* camFrustum, Transform* transform)
//{
//	//Get global scale thanks to our transform
//	XMVECTOR globalCenter = XMVector3Transform(XMLoadFloat4(&XMFLOAT4(mCenter.x, mCenter.y, mCenter.z, 1.0f)), XMLoadFloat4x4(&transform->GetWorldMatrix()));
//
//	// Scaled orientation
//	XMVECTOR right = XMLoadFloat3(&transform->GetDirectionX());
//	//right *= mExtents.x;
//	XMVECTOR up = XMLoadFloat3(&transform->GetDirectionY());
//	//up *= mExtents.y;
//	XMVECTOR forward = XMLoadFloat3(&transform->GetDirectionZ());
//	//forward *= mExtents.z;
//
//	XMFLOAT3 globalX = XMFLOAT3(1.0f, 0.0f, 0.0f);
//	float newIi;
//
//	XMStoreFloat(&newIi,
//		XMVectorAbs(XMVector3Dot(XMLoadFloat3(&globalX), right)) +
//		XMVectorAbs(XMVector3Dot(XMLoadFloat3(&globalX), up)) +
//		XMVectorAbs(XMVector3Dot(XMLoadFloat3(&globalX), forward)));
//
//	XMFLOAT3 globalY = XMFLOAT3(0.0f, 1.0f, 0.0f);;
//	float newIj;
//
//	XMStoreFloat(&newIj,
//		XMVectorAbs(XMVector3Dot(XMLoadFloat3(&globalY), right)) +
//		XMVectorAbs(XMVector3Dot(XMLoadFloat3(&globalY), up)) +
//		XMVectorAbs(XMVector3Dot(XMLoadFloat3(&globalY), forward)));
//
//	XMFLOAT3 globalZ = XMFLOAT3(0.0f, 0.0f, 1.0f);;
//	float newIk;
//
//	XMStoreFloat(&newIk,
//		XMVectorAbs(XMVector3Dot(XMLoadFloat3(&globalZ), right)) +
//		XMVectorAbs(XMVector3Dot(XMLoadFloat3(&globalZ), up)) +
//		XMVectorAbs(XMVector3Dot(XMLoadFloat3(&globalZ), forward)));
//
//	//We not need to divise scale because it's based on the half extention of the AABB
//	BoundingBox globalAABB(globalCenter, newIi, newIj, newIk);
//
//	return (globalAABB.isOnOrForwardPlane(camFrustum->GetLeftFace()) &&
//		globalAABB.isOnOrForwardPlane(camFrustum->GetRightFace()) &&
//		globalAABB.isOnOrForwardPlane(camFrustum->GetTopFace()) &&
//		globalAABB.isOnOrForwardPlane(camFrustum->GetBottomFace()) &&
//		globalAABB.isOnOrForwardPlane(camFrustum->GetNearFace()) &&
//		globalAABB.isOnOrForwardPlane(camFrustum->GetFarFace()));
//};