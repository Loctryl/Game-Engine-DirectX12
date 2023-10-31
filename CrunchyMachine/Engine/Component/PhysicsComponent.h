#pragma once
#include <iostream>
#include <vector>
#include "Engine/Component/Component.h"
#include "Resources/framework.h"

class BitMask;
class Transform;

class PhysicsComponent : public Component
{
public:
	PhysicsComponent(bool isRigid = false);
	~PhysicsComponent() = default;

	inline void SetVelocity(XMFLOAT3 velocity) { mVelocity = velocity; };
	inline void SetVelocity(float x, float y, float z) { mVelocity = {x, y, z}; };

	void Move(float deltaTime);

	inline XMFLOAT3 GetVelocity() { return mVelocity; };
	inline Transform* GetTransform() { return mTransform; };

	bool IsColliding(PhysicsComponent* a);
	inline bool IsRigid() { return mIsRigid; };

	XMFLOAT3 mGridPos = { 0, 0, 0 };

	inline BitMask* GetBitMask() { return mBitMask; };

private:
	Transform* mTransform;
	XMFLOAT3 mVelocity = { 0.0F , 0.0F, 0.0F };

	//to the physics component is Rigid ?
	bool mIsRigid;

	//Collision are only made of sphere, therefore, we save the radius of the collision sphere.
	float mRadius = 0;

	//The Bitmask is used to perform collision layers and avoid useless calculs.
	BitMask* mBitMask;
};