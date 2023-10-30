#pragma once
#include <iostream>
#include <vector>
#include "Engine/Component/Component.h"
#include "Resources/framework.h"

class Transform;

class PhysicsComponent : public Component
{
public:
	PhysicsComponent();
	~PhysicsComponent() = default;

	inline void AddFlag(std::wstring flag) { mFlags.push_back(flag); };

	std::vector<std::wstring> inline GetFlags() { return mFlags; };

	void RemoveFlag(std::wstring flag);

	void SetVelocity(XMFLOAT3 velocity);
	void SetVelocity(float x, float y, float z);

	void Move(float deltaTime);

	inline XMFLOAT3 GetVelocity() { return mVelocity; };
	inline Transform* GetTransform() { return mTransform; };

	bool IsColliding(PhysicsComponent* a);

	XMFLOAT3 mGridPos;

private:
	Transform* mTransform;
	XMFLOAT3 mVelocity = { 0.0F , 0.0F, 0.0F };

	float mRadius;
	std::vector<std::wstring> mFlags;
};