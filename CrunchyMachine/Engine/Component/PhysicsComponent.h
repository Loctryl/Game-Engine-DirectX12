#pragma once
#include <vector>
#include "Engine/Component/Component.h"
#include "EngineResources/framework.h"
#include "EngineResources/BitMask.h"
#include <iostream>
#include <algorithm>

class Transform;

class PhysicsComponent : public Component
{
public:
	PhysicsComponent(Transform* transform, bool isRigid , float radius = 0.0F, bool isStatic = false);
	~PhysicsComponent() = default;

	void Move(float deltaTime);

	float GetDistanceBetween(PhysicsComponent* a);

	inline void SetVelocity(XMFLOAT3 velocity) { mVelocity = velocity; };
	inline void SetVelocity(float x, float y, float z) { mVelocity = {x, y, z}; };
	inline void AddVelocity(XMFLOAT3 velocity) { mVelocity.x += velocity.x; mVelocity.y += velocity.y; mVelocity.z += velocity.z; };
	inline void AddVelocity(float x, float y, float z) { mVelocity.x += x; mVelocity.y += y; mVelocity.z += z; };

	inline void SetRotationVelocity(XMFLOAT3 velocity) { mRotationVelocity = velocity; };
	inline void SetRotationVelocity(float x, float y, float z) { mRotationVelocity = { x, y, z }; };
	inline void AddRotationVelocity(XMFLOAT3 velocity) { mRotationVelocity.x += velocity.x; mRotationVelocity.y += velocity.y; mRotationVelocity.z += velocity.z; };
	inline void AddRotationVelocity(float x, float y, float z) { mRotationVelocity.x += x; mRotationVelocity.y += y; mRotationVelocity.z += z; };

	inline void ClampVelocity(float mMin, float mMax) { mVelocity.x = std::clamp(mVelocity.x, mMin, mMax); mVelocity.y = std::clamp(mVelocity.y, mMin, mMax); mVelocity.z = std::clamp(mVelocity.z, mMin, mMax); };
	inline void ClampRotationVelocity(float mMin, float mMax) { mRotationVelocity.x = std::clamp(mRotationVelocity.x, mMin, mMax); mRotationVelocity.y = std::clamp(mRotationVelocity.y, mMin, mMax); mRotationVelocity.z = std::clamp(mRotationVelocity.z, mMin, mMax); };

	inline XMFLOAT3 GetRotationVelocity() { return mRotationVelocity; };
	inline XMFLOAT3 GetVelocity() { return mVelocity; };
	inline Transform* GetTransform() { return mTransform; };

	inline bool IsRigid() { return mIsRigid; };
	inline void SetRadius(float radius) { mRadius = radius; };
	inline float GetRadius() { return mRadius; };

	inline BitMask* GetBitMask() { return mBitMask; };
	inline void SetMask(int index) { mBitMask->SetMask(index); };
	inline bool HasCommonMask(BitMask* bitMask) { return mBitMask->HasCommonMask(bitMask); };
	inline void ClearBitMask() { mBitMask->Clear(); };

	XMFLOAT3 mGridPos = { 0,0,0 };

	bool mIsStatic = false;
private:
	Transform* mTransform;
	XMFLOAT3 mVelocity = { 0.0F , 0.0F, 0.0F };
	XMFLOAT3 mRotationVelocity = { 0.0F , 0.0F, 0.0F };

	//to the physics component is Rigid ?
	bool mIsRigid;


	//Collision are only made of sphere, therefore, we save the radius of the collision sphere.
	float mRadius;

	//The Bitmask is used to perform collision layers and avoid useless calculs.
	BitMask* mBitMask;
};