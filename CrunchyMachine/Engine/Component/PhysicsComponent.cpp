#include "PhysicsComponent.h"
#include "Engine/GameObject.h"
#include "Engine/Component/Transform.h"
#include <iostream>
#include <cmath>

PhysicsComponent::PhysicsComponent(Transform* transform, bool isRigid, float radius, bool isStatic)
{
	mComponentType = PHYSICS;
	mTransform = transform;
	mIsRigid = isRigid;
	mBitMask = new BitMask();
	mRadius = radius;
	mIsStatic = isStatic;
}

PhysicsComponent::~PhysicsComponent()
{
	mTransform = nullptr;
	RELPTR(mBitMask);
}


void PhysicsComponent::Move(float deltaTime)
{
	mTransform->Translate(mVelocity.x * deltaTime, mVelocity.y * deltaTime, mVelocity.z * deltaTime);
	mTransform->Roll(mRotationVelocity.z * deltaTime);
	mTransform->Pitch(mRotationVelocity.x * deltaTime);
	mTransform->Yaw(mRotationVelocity.y * deltaTime);
	XMFLOAT3 pos = mTransform->GetWorldPosition();

	mGridPos = { std::round(pos.x / GRID_SIZE), std::round(pos.y / GRID_SIZE), std::round(pos.z / GRID_SIZE) };
 }

float PhysicsComponent::GetDistanceBetween(PhysicsComponent* a) const
{
	XMFLOAT3 tempPos = a->GetTransform()->GetWorldPosition();
	XMFLOAT3 tempPos2 = mTransform->GetWorldPosition();

	float dist = std::sqrt(std::pow(tempPos.x - tempPos2.x, 2) + std::pow(tempPos.y - tempPos2.y, 2) + std::pow(tempPos.z - tempPos2.z, 2));
	dist -= (a->mRadius + mRadius);
	return dist;
}
