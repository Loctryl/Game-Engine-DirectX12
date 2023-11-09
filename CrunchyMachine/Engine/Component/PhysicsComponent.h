#pragma once
#include "Engine/Component/Component.h"
#include "EngineResources/framework.h"
#include "EngineResources/BitMask.h"
#include <algorithm>

class Transform;

// Manages for each game object his physic
class PhysicsComponent : public Component
{
private:
	Transform* mTransform;
	XMFLOAT3 mVelocity = { 0.0F , 0.0F, 0.0F };
	XMFLOAT3 mRotationVelocity = { 0.0F , 0.0F, 0.0F };

	//to the physics component is Rigid ?
	bool mIsRigid;
	
	//Collision are only made of sphere, therefore, we save the radius of the collision sphere.
	float mRadius;

	//The Bitmask is used to perform collision layers and avoid useless operations.
	BitMask* mBitMask;
	
public:
	XMFLOAT3 mGridPos = { 0,0,0 };

	bool mIsStatic = false;
	
	PhysicsComponent(Transform* transform, bool isRigid , float radius = 0.0F, bool isStatic = false);
	~PhysicsComponent() override;

	void Move(float deltaTime);

	float GetDistanceBetween(PhysicsComponent* a) const;

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

	inline XMFLOAT3 GetRotationVelocity() const { return mRotationVelocity; };
	inline XMFLOAT3 GetVelocity() const { return mVelocity; };
	inline Transform* GetTransform() const { return mTransform; };

	inline bool IsRigid() const { return mIsRigid; };
	inline void SetRadius(float radius) { mRadius = radius; };
	inline float GetRadius() const { return mRadius; };

	inline BitMask* GetBitMask() const { return mBitMask; };
	inline void SetMask(int index) const { mBitMask->SetMask(index); };
	inline bool HasCommonMask(BitMask* bitMask) const { return mBitMask->HasCommonMask(bitMask); };
	inline void ClearBitMask() const { mBitMask->Clear(); };
};